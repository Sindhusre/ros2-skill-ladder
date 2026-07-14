#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "my_robot_nodes/srv/battery_efficiency.hpp"

class Server :public rclcpp::Node {
 public:
   Server():Node("Server_"){
     auto topic_callback=
       [this](std_msgs::msg::Float64::UniquePtr msg)->void{
         auto drained +=(100-msg->data) ;
        auto timer +=1.0;};
     subscription_=this->create_subscription<std_msgs::msg::Float64>("battery_level",10,topic_callback);
  }
void efficiency(const std::shared_ptr<my_robot_nodes::srv::battery_efficiency::Request>request,
                std::shared_ptr<my_robot_nodes::srv::battery_efficiency::Response>Response){
                     response->x=request
                }

private:
    double rateofdrain(){
      if(timer ==0){
        return 0.0;
        }
      return drained/timer;
    }
    rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
    double drained=0.0; 
    double timer=1.0;
   };





