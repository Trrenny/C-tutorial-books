function [ObjIdx_List,ObjId_List,Strategy_List,offset_List,PredictTime_List,senario_cost_List] = senario_cost_prediction(obj_infos,NumofObj,vEgo,aEgo,Static_s,jerk_dec,jerk_inc,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max,v_up,v_low,a_min,a_max,Tconst,a_vec_his,delay_interval,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_ttc_min,P_wttc,P_chline_l_table,P_v_table,winner_ObjId_pre,winner_strategy_pre)
%calculate all cost lists for a lane using mpc and rss safety

%% input:
%       obj_infos:all objs for a lane
%       NumofObj:number of obj in a lane
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
%       a_min:min accerleration constrait in MPC
%       a_max:max accerleration constrait MPC
%       Tconst:time const for first order system
%       a_vec_his:history acceleration for delay compensation
%       delay_interval:time delay of accerleration in ego car
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
%       ObjIdx_List:all obj order index list for possible actions(for debug)  
%       ObjId_List: all obj id list for possible actions(for debug) 
%       Strategy_List:all stategy list for possible actions(for debug)
%       offset_List:all offset list for possible actions(for debug)
%       senario_cost_List: all cost list for possible actions(for debug)
%% step 0: initialize variables for all outputs

ObjIdx_List=zeros(NumofObj+2,1);
ObjId_List=zeros(NumofObj+2,1);
Strategy_List=zeros(NumofObj+2,1);
offset_List=zeros(NumofObj+2,1);
PredictTime_List=zeros(NumofObj+2,1);
senario_cost_List=zeros(NumofObj+2,1);
%% step 1: deal with all gaps(NumofObj obj, NumofObj+2 gaps, 1 for overtake first obj and 1 for behind last obj,NumofObj follow obj)
if NumofObj>0
    for i=1:NumofObj+2
        if(i==1)
            idx=double(i);
            [J,valid,Strategy_out,Counter,obj_idx,offset_tmp] = Function_mpc_cost_cal(obj_infos(idx),obj_infos(idx),vEgo,aEgo,Static_s,jerk_dec,jerk_inc,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max,v_up,v_low,a_min,a_max,Tconst,1,a_vec_his,delay_interval,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_ttc_min,P_wttc,P_chline_l_table,P_v_table,winner_ObjId_pre,winner_strategy_pre);
        elseif(i==NumofObj+1)
            idx=double(i-1);
            [J,valid,Strategy_out,Counter,obj_idx,offset_tmp] = Function_mpc_cost_cal(obj_infos(idx),obj_infos(idx),vEgo,aEgo,Static_s,jerk_dec,jerk_inc,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max,v_up,v_low,a_min,a_max,Tconst,2,a_vec_his,delay_interval,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_ttc_min,P_wttc,P_chline_l_table,P_v_table,winner_ObjId_pre,winner_strategy_pre);
        elseif(i==NumofObj+2)
            idx=double(i-2);
            [J,valid,Strategy_out,Counter,obj_idx,offset_tmp] = Function_mpc_cost_cal(obj_infos(idx),obj_infos(idx),vEgo,aEgo,Static_s,jerk_dec,jerk_inc,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max,v_up,v_low,a_min,a_max,Tconst,3,a_vec_his,delay_interval,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_ttc_min,P_wttc,P_chline_l_table,P_v_table,winner_ObjId_pre,winner_strategy_pre);
        else
            idx=double(i-1);
            [J,valid,Strategy_out,Counter,obj_idx,offset_tmp] = Function_mpc_cost_cal(obj_infos(idx),obj_infos(idx+1),vEgo,aEgo,Static_s,jerk_dec,jerk_inc,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max,v_up,v_low,a_min,a_max,Tconst,0,a_vec_his,delay_interval,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_ttc_min,P_wttc,P_chline_l_table,P_v_table,winner_ObjId_pre,winner_strategy_pre);
        end
        if(obj_idx==1)
            ObjIdx_List(i)=double(idx);
            ObjId_List(i)=obj_infos(idx).Id;
        else
            ObjIdx_List(i)=double(idx+1);
            ObjId_List(i)=obj_infos(idx+1).Id;
        end
        Strategy_List(i)=Strategy_out;
        offset_List(i)=offset_tmp;
        PredictTime_List(i)=Counter*0.1;
        if(valid==0)
            senario_cost_List(i)=1e6;
        else
            senario_cost_List(i)=J;
        end
    end
else
    senario_cost_List(1)=-1;
    senario_cost_List(2)=-1;
end