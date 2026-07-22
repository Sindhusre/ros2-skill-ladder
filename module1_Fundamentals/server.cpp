#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "my_robot_nodes/srv/battery_efficiency.hpp"

class Server :public rclcpp::Node {
 public:
   Server():Node("battery_server"){
     auto topic_callback=
       [this](std_msgs::msg::Float64::UniquePtr msg)->void{
         drained +=(100-msg->data) ;
         timer +=1.0;};
    subscription_=this->create_subscription<std_msgs::msg::Float64>("battery_level",10,topic_callback);
    service_=this->create_service<my_robot_nodes::srv::BatteryEfficiency>(
    "battery_efficiency",
     std::bind(
       &Server::efficiency,this,std::placeholders::_1,std::placeholders::_2);)
  }
 
     
  
 void efficiency(const std::shared_ptr<my_robot_nodes::srv::BatteryEfficiency::Request>request,
                std::shared_ptr<my_robot_nodes::srv::battery_efficiency::Response>response){
                     response->x=rateofdrain();
 //RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Incoming request \na : %s",request->a);
 RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"sending back the request : %0.2f",response->x);
                }

private:
    double rateofdrain(){
      if(timer ==0){
        return 0.0;
        }
      return drained/timer;
    }
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
    rclcpp::Service<my_robot_nodes::srv::BetteryEfficiency>::SharedPtr service_;
    double drained=0.0; 
    double timer=0.0;
   };
int main(int argc,char **argv){
 rclcpp::init(argc,argv);
 rclcpp::spin(
   std::make_shared<Server>());
 
 rclcpp::shutdown();
 return 0;
 
}





