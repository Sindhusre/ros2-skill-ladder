#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"
#include "my_robot_nodes/srv/batteryefficiency.hpp"

class Server :public rclcpp::Node {
 public:
   Server():Node("Server_"){
     auto topic_callback=
       [this](std_msgs::msg::Float64::UniquePtr msg)->void{
         drained +=(100-msg->data) ;
         timer +=1.0;};
     subscription_=this->create_subscription<std_msgs::msg::Float64>("battery_level",10,topic_callback);
  }
void efficiency(const std::shared_ptr<my_robot_nodes::srv::battery_efficiency::Request>request,
                std::shared_ptr<my_robot_nodes::srv::battery_efficiency::Response>Response){
                     response->x=rateofdrain();
 RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Incoming request \na : %s",request->a);
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
    double drained=0.0; 
    double timer=1.0;
   };
int main(int argc,char **argv){
 rclcpp::init(argc,argv);
 std::shared_ptr<rclcpp::Node>node =rclcpp::Node::make_shared("battery_efficiency_client");
 rcl::Service<my_robot_nodes::srv::battery_efficiency>::SharedPtr service=
 node->create_service<my_robot_nodes::srv::battery_efficiency>("add_two_ints");
 RCLCPP_INFO(rclcpp::get_logger("rclcpp"),"Ready to add two ints ");

 rclcpp::spin(node);
 rclcpp::shutdown();
 
 
}





