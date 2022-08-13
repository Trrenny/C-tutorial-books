function [x0_compensate] = delay_comp(x0,a_vec_his,delay_interval,Ts,T_hw,Tconst)
%predict error in furture delay_interval steps
A=[ 1, Ts, Tconst^2 - Tconst*Ts - T_hw*Tconst - Tconst^2*exp(-Ts/Tconst) + T_hw*Tconst*exp(-Ts/Tconst);
 0,  1,                                                             Tconst*exp(-Ts/Tconst) - Tconst;
 0,  0,                                                                             exp(-Ts/Tconst)];
B=[ -((Tconst*Ts^2)/2 - Tconst^3*(exp(-Ts/Tconst) - 1) - Tconst^2*Ts + T_hw*Tconst*Ts + T_hw*Tconst^2*(exp(-Ts/Tconst) - 1))/Tconst;
 -(Tconst*Ts + Tconst^2*(exp(-Ts/Tconst) - 1))/Tconst;
   1 - exp(-Ts/Tconst)];
x0_compensate=x0;
for i=1:delay_interval
    x0_compensate=A*x0_compensate+B*a_vec_his(delay_interval+1-i);
end

end

