#include "ros/ros.h"
#include "uss_cs/SLAESolver.h"
#include "std_msgs/Int32.h"
#include "std_msgs/Float32MultiArray.h"
#include <iostream>


ros::Publisher publisher;


bool solve(uss_cs::SLAESolver::Request &req,                                       //Функция-обработчик
    uss_cs::SLAESolver::Response &res)
{
  std_msgs::Float32MultiArray reply;                                               //Формируем сообщение для отправки
                                                                                   //Начало решения СЛАУ
  int n = 2;                                                                       //Порядок системы уравнений
  float a[n][n], b[n], x[n];
  a[0][0] = req.a11;
  a[0][1] = req.a12;
  b[0] = req.b1;
  a[1][0] = req.a21;
  a[1][1] =req.a22;
  b[1] = req.b2;
  float max;
  int k, index;
  const float eps = 0.01;                                                          //Точность

  k = 0;
  while (k < n)
  {
    max = std::abs(a[k][k]);                                                       //Поиск строки с максимальным a[i][k]
    index = k;
    for (int i = k + 1; i < n; i++)
    {
      if (std::abs(a[i][k]) > max)
      {
        max = std::abs(a[i][k]);
        index = i;
      }
    }
    
    if (max < eps)                                                                 //Перестановка строк
    {
      ROS_INFO("[]");                                                              //Отсутствие ненулевых диагональных элементов
      reply.data = res.result;
      publisher.publish(reply);
      return true;
    }
    for (int j = 0; j < n; j++)
    {
      float temp = a[k][j];
      a[k][j] = a[index][j];
      a[index][j] = temp;
    }
    float temp = b[k];
    b[k] = b[index];
    b[index] = temp;
    
    for (int i = k; i < n; i++)                                                    //Нормализация уравнений
    {
      float temp = a[i][k];
      if (std::abs(temp) < eps) continue;                                          //При условии нулевого коэффициента пропускаем
      for (int j = 0; j < n; j++)
        a[i][j] = a[i][j] / temp;
      b[i] = b[i] / temp;
      if (i == k)  continue;                                                       //Проверяем, не вычитается ли уравнение само из себя
      for (int j = 0; j < n; j++)
        a[i][j] = a[i][j] - a[k][j];
      b[i] = b[i] - b[k];
    }
    k++;
  }
  
  for (k = n - 1; k >= 0; k--)                                                     //Обратная подстановка
  {
    x[k] = b[k];
    for (int i = 0; i < k; i++)
      b[i] = b[i] - a[i][k] * x[k];
  }
                                                                                   //Конец решения СЛАУ
  ROS_INFO("[%.2f %.2f]", x[0], x[1]);
  res.result.push_back(x[0]);
  res.result.push_back(x[1]);
  reply.data = res.result;
  publisher.publish(reply);                                                        //Публикация результата в топик
  return true;
}

int main(int argc, char **argv)
{
    ros::init(argc,argv,"slae_server");
    ros::NodeHandle nh_;
    publisher = nh_.advertise <std_msgs::Float32MultiArray> ("slae_solver", 1000); //Подписываем сервис на чтение топика
    ros::ServiceServer service = nh_.advertiseService("slae_solver", solve);       //Ставим service на мониторинг сервиса с названием "slae_solver" 
    ROS_INFO("READY TO SOLVE SLAE");
    ros::spin();
    return 0;
}