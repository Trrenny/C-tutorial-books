function [u,x_next]= mpc_planner(x_current,jerk_dec,jerk_inc,a_min,a_max,N,v_ego,v_up,v_low,T_hw,Tconst,Ts)
%prediciton horizon
%state weight in obj function
q=1*[1 0 0;0 1 0;0 0 0];
%control weight in obj function
r=1*eye(1);
%ini states
x0=x_current;
l=length(x0);
%% conti model to discrete model
A=[ 1, Ts, Tconst^2 - Tconst*Ts - T_hw*Tconst - Tconst^2*exp(-Ts/Tconst) + T_hw*Tconst*exp(-Ts/Tconst);
    0,  1,                                                             Tconst*exp(-Ts/Tconst) - Tconst;
    0,  0,                                                                             exp(-Ts/Tconst)];
B=[ -((Tconst*Ts^2)/2 - Tconst^3*(exp(-Ts/Tconst) - 1) - Tconst^2*Ts + T_hw*Tconst*Ts + T_hw*Tconst^2*(exp(-Ts/Tconst) - 1))/Tconst;
    -(Tconst*Ts + Tconst^2*(exp(-Ts/Tconst) - 1))/Tconst;
    1 - exp(-Ts/Tconst)];
%% cal terminal cost (Riccati equations by dare,q=1,r=1)
if(r==1)
    Pf=[19.6329   13.2908   -2.0022;
        13.2908   23.9269   -3.8198;
        -2.0022   -3.8198    0.6575];
elseif(r==5)
    Pf=[  25.7830   26.9489   -4.4741;
        26.9489   64.1608  -11.2997;
        -4.4741  -11.2997    2.0512];
elseif(r==10)
    Pf=[  29.4760   36.9679   -6.3264;
        36.9679  101.2916  -18.3187;
        -6.3264  -18.3187    3.3798];
else
    Pf=[19.6329   13.2908   -2.0022;
        13.2908   23.9269   -3.8198;
        -2.0022   -3.8198    0.6575];
end
%% stack model cal

A_hat=zeros(l*N,l);
B_hat=zeros(l*N,N);
for i=1:N
    A_hat(1+(i-1)*l:i*l,:)=A^i;
end
for i=1:N
    for j=1:i
        B_hat(1+(i-1)*l:i*l,j)=A^(i-1)*B;
    end
end
%% construct Q,R
Q=zeros(l*N,l*N);
R=zeros(N,N);
for i=1:N
    if(i<N)
        Q(1+(i-1)*l:i*l,1+(i-1)*l:i*l)=q;
    else
        Q(1+(i-1)*l:i*l,1+(i-1)*l:i*l)=q+Pf;
    end
    R(i,i)=r;
end
H=B_hat'*Q*B_hat+R;
f=B_hat'*Q*A_hat*x0;
%% solve optimization problem by direct search
if(v_ego>v_up)
    a_max=0;
elseif(v_ego<v_low)
    a_min=0;
end

p=exp(-Ts/Tconst);
a_lb=-Ts*jerk_dec/(1-p)+x_current(3);
a_lb=max(a_lb,a_min);
a_up=Ts*jerk_inc/(1-p)+x_current(3);
a_up=min(a_up,a_max);
u_vec=-inv(H)*f;

for i=1:1
    u_vec(i)=max(a_lb,min(u_vec(i),a_up));
end
%
if(v_ego>v_up)
    if(a_up<a_lb)
        u_vec(1)=a_lb;
    end
elseif(v_ego<v_low)
    if(a_up<a_lb)
        u_vec(1)=a_up;
    end
end

x_next=A*x_current+B*u_vec(1);
u=u_vec(1);
% J_min=1e8;
% u=0;
% for a=-5:interval:3
%     x_next=A*x_current+B*a;
%     if(abs((x_next(3)-x_current(3))/Ts)<=5)
%         Jtmp=0.5*a'*H*a+f'*a;
%         if(Jtmp<J_min)
%             u=a;
%             valid=1;
%             J_min=Jtmp;
%         end
%     end
% end

end

