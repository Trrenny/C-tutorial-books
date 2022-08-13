function [offset_searched]=Function_golden_search (offset_low,offset_up,dObj,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval)

x0_local=x0;

x0_local(1)=dObj+offset_low;
[~,~,v_ego_low,~,valid_low] = mpc_predictor(3,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_local,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,offset_low,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out ,0,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);

x0_local(1)=dObj+offset_up;
[~,~,v_ego_up,~,valid_up] = mpc_predictor(3,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_local,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,offset_up,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out ,0,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
if(0 == valid_low)
    v_ego_low = 0;
end
if(0 == valid_up)
    v_ego_up = 0;
end
gr = 1.618033989;
a = offset_low;
b = offset_up;
t = (b-a)/gr;
c = b - t;
d = a + t;

while(abs(c - d) > 0.3)
    x0_local(1)=dObj+c;
    [~,~,v_ego_c,~,valid_c] = mpc_predictor(3,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_local,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,c,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out ,0,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
    if(0 == valid_c)
        v_ego_c = 0;
    end
    
    x0_local(1)=dObj+d;
    [~,~,v_ego_d,~,valid_d] = mpc_predictor(3,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_local,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,d,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out ,0,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
    if(0 == valid_d)
        v_ego_d = 0;
    end
    
    if(v_ego_c>=v_ego_d)
        b = d;
    else
        a = c;
    end
    t = (b-a)/gr;
    c = b - t;
    d = a + t;
end

    x0_local(1)=dObj+a;
    [~,~,v_ego_a,~,valid_a] = mpc_predictor(3,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_local,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,a,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out ,0,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
    if(0 == valid_a)
        v_ego_a = 0;
    end
    
    x0_local(1)=dObj+b;
    [~,~,v_ego_b,~,valid_b] = mpc_predictor(3,Static_s,halfofObjVehicleLength,P_rearAxle2FrontOverhang,P_rearAxle2RearOverhang,v_up,v_low,a_min,a_max,x0_local,T_hw,Tconst,Ts,NN,vObj,jerk_dec,jerk_inc,b,rho,acc_max,a_brake_min,a_brake_max,N,P_Pathlength_Gain_In,P_Pathlength_Gain_Out ,0,P_predictor_vMin,P_predictor_vMax,P_chline_l_table,P_v_table,a_vec_his,delay_interval);
    if(0 == valid_b)
        v_ego_b = 0;
    end
v_all=[v_ego_low;v_ego_a;v_ego_b;v_ego_up];
v_index=[offset_low;a;b;offset_up];
[~,ind]=max(v_all);
offset_searched=v_index(ind,1);
