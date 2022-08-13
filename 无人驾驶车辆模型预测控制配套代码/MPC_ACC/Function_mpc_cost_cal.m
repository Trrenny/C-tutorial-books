function [J,valid,Strategy,Counter,obj_idx,offset] = Function_mpc_cost_cal(obj_info,obj_info_second,vEgo,aEgo,Static_s,jerk_dec,jerk_inc,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max,v_up,v_low,a_min,a_max,Tconst,search_mode,a_vec_his,delay_interval,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_ttc_min,P_wttc,P_chline_l_table,P_v_table,winner_ObjId_pre,winner_strategy_pre)
%predicition by mpc,  calculated  senario validity, senario predicition
%time ,the offset to follow obj,cost J

%% input:
%       obj_info:first obj
%       obj_info_second:second obj
%       vEgo: ego speed
%       aEgo: ego accerleration
%       Static_S: distance to static obstacal in current lane
%       jerk: jerk constaint in MPC
%       P_rearAxle2FrontOverhang&P_rearAxle2RearOverhang: distance of rear
%       axle to front bump and rear bump
%       rho: reaction time in rss 
%       acc_max: max accerleration in acc
%       a_brake_min: min brake 
%       a_brake_max: max brake 
%       a_min:min acceleration constrait in MPC
%       a_max:max acceleration constrait MPC
%       Tconst:time const for first order system
%       search_mode:0 gap searching, 1 overtake first obj, 2 behind first
%       obj,3 far behind last objs
%       a_vec_his:history acceleration for delay compensation
%       delay_interval:time delay of acceleration in ego car
%       N:mpc prediction interval
%       P_Pathlength_Gain_In: gain for hysteresis(in gain for enough space) 
%       P_Pathlength_Gain_Out:gain for hysteresis(out gain for enough space)
%       P_predictor_vMin: low speed threshold in mpc prediction for a valid senario
%       P_ttc_min: min time to collision (for cost calculation,k_t1*t1+P_wttc*max(P_ttc_min-t2,0))
%       P_wttc:  weight for time to collision (for cost calculation,k_t1*t1+P_wttc*max(P_ttc_min-t2,0))
%       P_chline_l_table: look up table for lateral planning length
%       P_v_table: look up table for speed
%       winner_ObjId_pre:previous step winner ID (for enbale hysteresis) 
%       winner_strategy_pre:previous step winner stategy(for enbale hysteresis) 
%% output:
%       J:cost  
%       valid: senario validity
%       Strategy:Strategy 1 overtake obj, 2 follow obj 3, far behind obj
%       Counter: time counter to achieve safety
%       obj_idx: 1 first obj 2 second obj
%       offset: offset to follow obj


%% step 0: initialize variables for all ouputs and parameters
J=1e6;
Counter=0;
valid=0;
Strategy=-1;
obj_idx=1;
offset=0;
%step 0.1: set parameters
coef=1.1;
T_hw=0;
Ts=0.1;
NN=200;

dObj = obj_info.relative_dis;
vObj = obj_info.veloctiy;
x0=zeros(3,1);
halfofObjVehicleLength=obj_info.length/2;
%% step 1: rss saft checker to calculate min safety distance
[d_min,~] = rss_safe_checker(vObj,vObj,0,rho,acc_max,a_brake_min,a_brake_max);
%% step 2: cal offset&Strategy using search_mode
if(search_mode==1)
    %%step 2.1: overtake obj
    Strategy=1;
    offset=coef*d_min+P_rearAxle2RearOverhang+halfofObjVehicleLength;
elseif(search_mode==2)
    %%step 2.2: behind obj
    Strategy=2;
    offset=-coef*d_min-P_rearAxle2FrontOverhang-halfofObjVehicleLength;
elseif(search_mode==3)
    %%step 2.3: far behind obj
    Strategy=3;
    %     vEnd=zeros(60,1);
    %     S3_offset=linspace(-10,-100,60);
    %     for i=1:60
    %         offset=S3_offset(i);
    %         x0(1)=dObj+offset;
    %         x0(2)=vObj-vEgo;
    %         x0(3)=aEgo;
    %         [~,~,v_ego,~,valid] = mpc_predictor(Strategy,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,a_min,a_max,x0,T_hw,Tconst,Ts,NN,vObj,jerk,offset,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,0,P_predictor_vMin,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
    %         if valid~=0
    %             vEnd(i)=v_ego;
    %         end
    %     end
    %     [~,index]=max(vEnd);
    %     offset=S3_offset(index);
    x0_1=[dObj+offset;vObj-vEgo;aEgo];
    offset = Function_golden_search (-10,-100,dObj,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_1,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
else
    %%step 2.4: gap find between two objs
    dObj_second = obj_info_second.relative_dis;
    gap_b2b=dObj-dObj_second-obj_info.length/2-obj_info_second.length/2;
    if(gap_b2b<2*max(d_min,0)+8)
        return
    else
        if(gap_b2b>3*d_min+5)
            offset1=-coef*d_min-P_rearAxle2FrontOverhang-obj_info.length/2;
            offset2=coef*d_min+P_rearAxle2RearOverhang+obj_info_second.length/2;
            [~,idx]=min(abs([obj_info.relative_dis+offset1 obj_info_second.relative_dis+offset2]));
            if(idx==1)
                obj_idx=1;
                dObj=obj_info.relative_dis;
                offset=offset1;
                Strategy=2;
            else
                obj_idx=2;
                dObj=obj_info_second.relative_dis;
                vObj=obj_info_second.veloctiy;
                offset=offset2;
                Strategy=1;
                halfofObjVehicleLength=obj_info_second.length/2;
            end
        else
            Strategy=2;
            offset=-gap_b2b/2-obj_info.length/2;
        end
    end
end

%% step 3: mpc predicion
%step 3.1: mpc initial state cal
x0(1)=dObj+offset;
x0(2)=vObj-vEgo;
x0(3)=aEgo;
%step 3.2: return condition
if(vObj<1&&x0(1)<0) %% never select too slow obj behind
    valid=0;
    J=1e6;
    return;
end
%step 3.3: Enable Hysteresis logic for previous consistent senario
if(obj_idx==1&&winner_ObjId_pre==obj_info.Id&&winner_strategy_pre==Strategy)
    Enable_Hysteresis=1;
elseif(obj_idx==2&&winner_ObjId_pre==obj_info_second.Id&&winner_strategy_pre==Strategy)
    Enable_Hysteresis=1;
else
    Enable_Hysteresis=0;
end
%step 3.4: mpc predicion
[~,s_left,v_ego,cnt,valid] = mpc_predictor(Strategy,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,offset,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,Enable_Hysteresis,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
%% step 4: predicion cost and time calculation
t1=cnt*0.1;%time to arrive safe gap,effciency
t2=(s_left)/v_ego; %time to collision(to static obs),safy to user
k_t1=1;
k_t2=0;
if v_ego>vEgo
    k_t2=P_wttc;
end
J=k_t1*t1+k_t2*max(P_ttc_min-t2,0); %%overall cost function
Counter=cnt;
end