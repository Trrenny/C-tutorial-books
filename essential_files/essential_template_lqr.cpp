#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
using namespace std;

const double CaculateDesiredLonAccLqr(const double ego_speed, const double ego_acc,
	const double target_speed, const double target_distance,
	const double curr_distance, const double delay_time,
	const double beta1, const double beta2, const double beta3,
	const double beta4, const double beta5, double& debug, double& debug2)
{
	constexpr uint32_t N1 = 100;//循环次数
	constexpr double KTimestep = 0.1;
	constexpr double kMAxdec = -3;//最大的减速度
	constexpr double kMaxacc = 2;//最大的加速度
	const double jerklimit = 3.0;//jerk的限制

	Eigen::Matrix<double, 4, 4> weightMatrix_Q1;
	Eigen::Matrix<double, 1, 4> weightMatrix_R1;
	std::vector<Eigen::Matrix<double, 1, 1>> matrixP1;
	std::vector<Eigen::Matrix<double, 1, 4>> matrixG1;
	std::vector<Eigen::Matrix<double, 4, 4>> matrixS1;
	std::vector<Eigen::Matrix<double, 4, 4>> matrixQ1;
	std::vector<Eigen::Matrix<double, 4, 1>> matrixD1;
	std::vector<Eigen::Matrix<double, 1, 1>> matrixE1;
	std::vector<Eigen::Matrix<double, 1, 1>> matrixH1;
	std::vector<Eigen::Matrix<double, 4, 1>> matrixT1;
	Eigen::Matrix<double, 4, 1> matrixC1;
	Eigen::Matrix<double, 4, 1> matrixA_prime;
	Eigen::Matrix<double, 4, 1> matrixB_prime;
	std::vector<Eigen::Matrix<double, 3, 1>> x1;
	std::vector<Eigen::Matrix<double, 1, 1>> u1;
	std::vector<Eigen::Matrix<double, 4, 1>> z;
	std::vector<Eigen::Matrix<double, 1, 1>> delta_u;
	matrixP1.resize(N1);
	matrixG1.resize(N1);
	matrixS1.resize(N1);
	matrixQ1.resize(N1+1);
	matrixD1.resize(N1+1);
	matrixE1.resize(N1+1);
	matrixH1.resize(N1);
	matrixT1.resize(N1);
	x1.resize(N1 + 1);
	u1.resize(N1);
	z.resize(N1 + 1);
	delta_u.resize(N1);

	double beta1_gain = 1.0;
	double beta2_gain = 1.0;
	double beta3_gain = 1.0;
	double beta4_gain = 1.0;
	double delay_gain = 1.0;

	//define:calibrated parameters
	matrixC1 << 0, 0, 0.0 * KTimestep / delay_time, 0;
	x1[0] << target_distance - curr_distance, target_speed - ego_speed, 0.0 - ego_acc;
	weightMatrix_Q1 << beta1_gain * beta1, 0, 0, 0,
		0, beta2_gain* beta2, 0, 0,
		0, 0, beta3_gain* beta3, 0,
		0, 0, 0, beta4_gain* beta4;
	weightMatrix_R1 << 1 * beta5;
	

	//solve
	matrixQ1[N1] = weightMatrix_Q1;
	matrixD1[N1].setZero(4, 1);
	matrixE1[N1].setZero(1, 1);

	matrixA_prime << 1, -KTimestep, 0, 0,
		0, 1, KTimestep, 0,
		0, 0, 1 - KTimestep / delay_time, -KTimestep / delay_time,
		0, 0, 0, 1;


	matrixB_prime << 0, 0, -KTimestep / delay_time, 1;
	z[0] << x1[0], ego_acc;

	for (int k = N1; k > 0; k--)
	{
		matrixP1[k - 1] = (weightMatrix_R1 + matrixB_prime.transpose() * matrixQ1[k] * matrixB_prime).inverse();
		matrixG1[k - 1] = -matrixP1[k - 1] * matrixB_prime.transpose() * matrixQ1[k] * matrixA_prime;
		matrixH1[k - 1] = -matrixP1[k - 1] * matrixB_prime.transpose() * (matrixQ1[k] * matrixC1 + matrixD1[k]);
		matrixS1[k - 1] = matrixA_prime + matrixB_prime * matrixG1[k - 1];
		matrixT1[k - 1] = matrixB_prime = matrixH1[k - 1] + matrixC1;
		matrixQ1[k - 1] = matrixG1[k - 1].transpose() * weightMatrix_R1 * matrixG1[k - 1] + matrixS1[k - 1].transpose() * matrixQ1[k] * matrixS1[k - 1] + weightMatrix_Q1;
		matrixD1[k - 1] = matrixG1[k - 1].transpose() * weightMatrix_R1 * matrixH1[k - 1] + matrixS1[k - 1].transpose() * matrixQ1[k] * matrixT1[k - 1] + matrixS1[k - 1].transpose() * matrixD1[k];
		matrixE1[k - 1] = (static_cast<double>(0.5)) * matrixH1[k - 1].transpose() * weightMatrix_R1 * matrixH1[k - 1] + (static_cast<double>(0.5)) * matrixT1[k - 1].transpose() * matrixQ1[k] * matrixT1[k - 1] + matrixA_prime;




	}
	u1[0] = matrixG1[0] * z[0] + matrixH1[0];
	z[1] = matrixA_prime * z[0] + matrixB_prime * u1[0] + matrixC1;
	debug = z[1](3, 0);
	z[1](3, 0) = std::min(std::max(z[1](3, 0), kMAxdec), kMaxacc);//限制加速度在最大减速度和最大加速度之间
	debug2 = z[1](3, 0);
	const double temp_acc = z[1](3, 0);
	return z[1](3, 0);

}

int main_(int argc, char* argv[])
{
#define CTOD(num) atof(argv[num])
	double ego_speed{ CTOD(1) }, ego_acc{ CTOD(2) }, target_speed{ CTOD(3) }, target_distacne{ CTOD(4) }, curr_distance{ CTOD(5) },
		delay_time{ CTOD(6) }, beta1{ CTOD(7) }, beta2{ CTOD(8) }, beta3{ CTOD(8) }, beta4{ CTOD(9) }, beta5{CTOD(10)};
	std::ofstream ofile("lqr.txt", std::ios::trunc);
	if (!ofile.is_open())
		std::cout << "can not open this file" << std::endl; return;
	if (argc == 12)//重要
	{
	}
	else
	{
		std::cout << "FATAL ERROR:TOO FEW " << std::endl;
		std::ofstream ofile2("lqr_debug.txt", std::ios::trunc);
		for (int i{}; i < argc; i++)
		{
			std::cout << argv[i] << std::endl;
			ofile2 << argv[i] << std::endl;
		}
		ofile << "0" << std::endl;
		ofile.close();
		ofile2.close();
		return -99;
	}

	double debug_z{}, debug_z2{};
	double acc = CaculateDesiredLonAccLqr(ego_speed, ego_acc, target_speed, target_distacne, curr_distance, delay_time, beta1, beta2, beta3, beta4, beta5, debug_z, debug_z2);
	ofile << acc << std::endl;
	ofile.close();
	std::ofstream ofile2("lqr_debug.txt", std::ios::app | std::ios::in | std::ios::out);


#define VAR(a) #a << "=" << a << " "
	ofile2 << VAR(ego_speed) << VAR(ego_acc) << VAR(target_speed) << VAR(target_distacne) << VAR(curr_distance) << VAR(delay_time) << VAR(acc) << VAR(debug_z) << VAR(debug_z2) << std::endl;
	ofile2.close();
	std::cout << acc << std::endl;
	return 0;
}
