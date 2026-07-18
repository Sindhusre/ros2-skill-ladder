#include "rclcpp/rclcpp.hpp"
#include "my_robot_nodes/srv/batteryefficiency.hpp"

#include <chrono>
#include<cstdlib>
#include <memory>
using namespace std::chrono_literals;

int main(int argc,char **argv)
{
 rclcpp::init(argc,argv);

  if(argc==1){
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"we need drain rate ");
    return 1;
  }
  std::shared_ptr<rclcpp::Node>node =rclcpp::Node::make_shared("battery_efficiency_client");
  rclcpp::Client<my_robot_nodes::srv::BatteryEfficiency>::SharedPtr client=
  node->create_client<my_robot_node::srv::BatteryEfficiency>("battery_efficiency");

  auto request=std::make_shared<my_robot_nodes::srv::BatteryEfficiency::Request>();

  //request->a="battery";
  while (!client->wait_for_service(1s)){
    if(!rclcpp::ok()){
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"Interrupted while waiting for the service.Exiting.");
       return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"service not available ,waiting again ..");
  }
  auto result = client->async_send_request(request);
  if(rclcpp::spin_until_future_complete(node,result)==
     rclcpp::FutureReturnCode::SUCCESS)
  {
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"drain: %.2f",result.get()->x);
  }else{
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"),"Failed to call service drain_rate");
  }
  rclcpp::shutdown();
  return 0;
}
