clc
clear
T_hw=1.5;
d0=5;
v_p=20;
sim_Time=200;
Tconst=0.2;
Ts=0.1;
u_vec=zeros(sim_Time,1);
x_vec=zeros(3,1,200);
A=[0 1 0;0 0 -1;0 0 -1/Tconst];
B=[0;0;1/Tconst];
C=eye(3);
D=zeros(3,1);
x0=[23;0;0];
sys = ss(A,B,C,D);
sysd = c2d(sys,Ts);

x_current=x0;
s_vec=zeros(sim_Time+1,1);
v_vec=zeros(sim_Time+1,1);
vh_vec=zeros(sim_Time+1,1);
s_vec(1)=x0(1);
v_vec(1)=x0(2)+v_p;
vh_vec(1)=x0(3);
for i=1:sim_Time
    x_current_in=x_current;
    x_current_in(1)=x_current(1)-T_hw*(v_p-x_current(2))-d0;
    [u_vec(i),valid]=MPC_controller(x_current_in,T_hw,Tconst,Ts);
    if(~valid)
        u_vec(i)=-100;
    end
    x_current=sysd.A*x_current+sysd.B*u_vec(i);
    x_vec(:,:,i)=x_current;
    s_vec(i+1)=x_current(1);
    v_vec(i+1)=-x_current(2)+v_p;
    vh_vec(i+1)=x_current(3);
end
time_vec=0:Ts:(sim_Time-1)*Ts;
figure(1)
ax1=subplot(4,1,1);
plot(time_vec,s_vec(1:sim_Time))
legend('d\_rel')

ax2=subplot(4,1,2);
plot(time_vec,v_vec(1:sim_Time))
legend('v\_rel')

ax3=subplot(4,1,3);
plot(time_vec,vh_vec(1:sim_Time))
legend('vh\_der')

ax4=subplot(4,1,4);
plot(time_vec,u_vec(1:sim_Time))
legend('a')

linkaxes([ax1,ax2,ax3,ax4],'x')

