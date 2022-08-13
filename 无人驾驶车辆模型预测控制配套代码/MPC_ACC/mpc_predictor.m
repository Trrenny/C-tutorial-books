function [s_ego,s_left,v_ego,cont,valid] = mpc_predictor(Strategy,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0,T_hw,Tconst,Ts,NN,v_obj,jerk_dec,jerk_inc,offset,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,Enable_Hysteresis,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval)
%predicition by mpc,  calculated  senario validity, senario predicition
%time , distance to travel for safety, left distance to static obstacle
%,,P_chline_l_table,P_v_table,a_vec_his,delay_interval
%% input:
%       Strategy:Strategy 1 overtake obj, 2 follow obj 3, far behind obj
%       Static_S: distance to static obstacal in current lane
%       halfofObjVehicleLength: half Vehicle Length
%       P_rearAxle2FrontOverhang&P_rearAxle2RearOverhang: distance of rear
%       axle to front bump and rear bump
%       a_min:min acceleration constrait in MPC
%       a_max:max acceleration constrait MPC
%       x0:initial state in mpc
%       T_hw:time head way for mpc
%       Tconst:time const for first order system
%       Ts: sampling time
%       NN:predition time 
%       v_obj:obj speed
%       jerk:jerk constaint in MPC
%       offset: offset to follow obj
%       rho: reaction time in rss 
%       acc_max: max accerleration in acc
%       a_brake_min: min brake 
%       a_brake_max: max brake 
%       N: prediction horizon in mpc controller
%       P_Pathlength_Gain_In: gain for hysteresis(in gain for enough space) 
%       P_Pathlength_Gain_Out:gain for hysteresis(out gain for enough space
%       Enable_Hysteresis: enable Hysteresis flag
%       P_predictor_vMin: low speed threshold in mpc prediction for a valid senario
%       P_chline_l_table: look up table for lateral planning length
%       P_v_table: look up table for speed
%       a_vec_his:history acceleration for delay compensation
%       delay_interval:time delay of acceleration in ego car

%% output:
%       s_ego:cost  
%       s_left: senario validity
%       v_ego:Strategy 1 overtake obj, 2 follow obj 3, far behind obj
%       cont: time counter to achieve safety
%       valid: senario validity


u=zeros(NN,1);
s_left=0;
valid=0;
cont=0;
safe_in_delay=0;
%% step 0: initial system model and initial state 
A=[ 1, Ts, Tconst^2 - Tconst*Ts - T_hw*Tconst - Tconst^2*exp(-Ts/Tconst) + T_hw*Tconst*exp(-Ts/Tconst);
    0,  1,                                                             Tconst*exp(-Ts/Tconst) - Tconst;
    0,  0,                                                                             exp(-Ts/Tconst)];
B=[ -((Tconst*Ts^2)/2 - Tconst^3*(exp(-Ts/Tconst) - 1) - Tconst^2*Ts + T_hw*Tconst*Ts + T_hw*Tconst^2*(exp(-Ts/Tconst) - 1))/Tconst;
    -(Tconst*Ts + Tconst^2*(exp(-Ts/Tconst) - 1))/Tconst;
    1 - exp(-Ts/Tconst)];
x0_compensate=x0;

d_rel=x0_compensate(1)-offset;
s_ego=0;
v_ego=v_obj-x0_compensate(2);
%% step 1: delay compensate
for i=1:delay_interval
    if v_ego<P_predictor_vMin||v_ego>P_predictor_vMax
        break
    end
    dis= interp1(P_v_table,P_chline_l_table,min(80/3.6,max(0,v_ego)),'linear');
    l_In=dis*P_Pathlength_Gain_In;
    l_Out=dis*P_Pathlength_Gain_Out;
    [~,fesibility] = rss_safe_checker_mode(v_ego,v_obj,Strategy,d_rel,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max);
    if(Strategy==1&&fesibility)
        if (Static_s>s_ego+l_In||(Enable_Hysteresis==1&&Static_s>s_ego+l_Out))
            valid=1;
            s_left=Static_s-s_ego;
            safe_in_delay=1;
        end
        break
    end
    if(Strategy==2&&fesibility)
        if (Static_s>s_ego+l_In||(Enable_Hysteresis==1&&Static_s>s_ego+l_Out))
            valid=1;
            s_left=Static_s-s_ego;
            safe_in_delay=1;
        end
        break
    end
    if(Strategy==3&&fesibility)
        if (Static_s>s_ego+l_In||(Enable_Hysteresis==1&&Static_s>s_ego+l_Out))
            valid=1;
            s_left=Static_s-s_ego;
            safe_in_delay=1;
            break
        end
    end
    
    x0_compensate=A*x0_compensate+B*a_vec_his(delay_interval+1-i);
    d_rel=x0_compensate(1)-offset;
    s_ego=(v_obj-x0_compensate(2))*Ts+s_ego+1/2*x0_compensate(3)*(Ts^2);
    v_ego=v_obj-x0_compensate(2);
    cont=cont+1;
end

%% step 2: mpc predicion for NN steps
if(~safe_in_delay)
    x_next=x0_compensate;
    Static_s_comp=Static_s-s_ego;
    d_rel=x_next(1)-offset;
    s_ego=0;
    v_ego=v_obj-x_next(2);
    for i=1:NN
        x_current=x_next;
        if v_ego<P_predictor_vMin||v_ego>P_predictor_vMax
            break
        end
        dis= interp1(P_v_table,P_chline_l_table,min(80/3.6,max(0,v_ego)),'linear');
        l_In=dis*P_Pathlength_Gain_In;
        l_Out=dis*P_Pathlength_Gain_Out;
        [~,fesibility] = rss_safe_checker_mode(v_ego,v_obj,Strategy,d_rel,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,rho,acc_max,a_brake_min,a_brake_max);
        if(Strategy==1&&fesibility)
            if(Static_s_comp>s_ego+l_In||(Enable_Hysteresis==1&&Static_s_comp>s_ego+l_Out))
                valid=1;
                s_left=Static_s_comp-s_ego;
            end
            break
        end
        if(Strategy==2&&fesibility)
            if(Static_s_comp>s_ego+l_In||(Enable_Hysteresis==1&&Static_s_comp>s_ego+l_Out))
                valid=1;
                s_left=Static_s_comp-s_ego;
            end
            break
        end
        if(Strategy==3&&fesibility)
            if (Static_s_comp>s_ego+l_In||(Enable_Hysteresis==1&&Static_s_comp>s_ego+l_Out))
                valid=1;
                s_left=Static_s_comp-s_ego;
                break
            end
        end
        %% step3.1: mpc controller for predicion, calculate u and x next
        %[u(i),x_next]=mpc_planner(x_current,jerk,a_min,a_max,N,T_hw,Tconst,Ts,0.1);
         [u(i),x_next]=mpc_planner(x_current,jerk_dec,jerk_inc,a_min,a_max,N,v_ego,v_up,v_low,T_hw,Tconst,Ts);
        d_rel=x_next(1)-offset;
        s_ego=(v_obj-x_next(2))*Ts+s_ego+1/2*x_next(3)*(Ts^2);
        v_ego=v_obj-x_next(2);
        cont=cont+1;
    end
end

end

