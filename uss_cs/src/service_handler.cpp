#include "ros/ros.h"
#include "uss_cs/SLAESolver.h"
#include <iostream>

int main(int argc, char **argv)
{
    ros::init(argc,argv,"slae_solver_publisher");
    ros::NodeHandle nh_;
    
    ros::ServiceClient client = nh_.serviceClient<uss_cs::SLAESolver>("slae_solver"); //Подписываем client на отправку сообщений в сервис "slae_solver"
    uss_cs::SLAESolver srv;

    while (ros::ok())
    {
        float in[6];

        std::cout << "a11:";    
        std::cin >> in[0];
        std::cout << "a21:";    
        std::cin >> in[1];
        std::cout << "b1:";    
        std::cin >> in[2];
        std::cout << "a21:";    
        std::cin >> in[3];
        std::cout << "a22:";    
        std::cin >> in[4];
        std::cout << "b2:";    
        std::cin >> in[5];     

        srv.request.a11 = in[0];
        srv.request.a12 = in[1];
        srv.request.b1 = in[2];
        srv.request.a21 = in[3];
        srv.request.a22 = in[4];
        srv.request.b2 = in[5];
        
        if (client.call(srv))
        {
            ROS_INFO("[%.2f %.2f]", srv.response.result[0], srv.response.result[1]);
        }
        else
        {
            std::cout<<"Failed to call service slae_solver"<<std::endl;
            return 1;
        }
    }

    return 0;
}