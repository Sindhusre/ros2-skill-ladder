#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

class Batterylevel_subscriber :public rclcpp ::Node
{
public:
  Batterylevel_subscriber():Node("Batterylevel_subscriber"){
    auto topic_callback=
       [this](std_msgs::msg::Float64::UniquePtr msg)->void{
         RCLCPP_INFO(this->get_logger(),"the battery level is: %.2f",msg->data);
         if(msg->data>50.00){
           RCLCPP_INFO(this->get_logger(),"the battery level is good");
         }
         
         else if(msg->data>20.00){
           RCLCPP_WARN(this->get_logger(),"please charge");
          }
         else if(msg->data>5.00){
           RCLCPP_ERROR(this->get_logger(),"CRITICAL please charge");
          }
         else{
           RCLCPP_FATAL(this->get_logger(),"battery is dying");
         }
       };
     subscription_=
       this->create_subscription<std_msgs::msg::Float64>("battery_level",10,topic_callback);
  }
 private:
       rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};
int main(int argc , char *argv[]){
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Batterylevel_subscriber>());
  rclcpp::shutdown();
  return 0;
  
}
