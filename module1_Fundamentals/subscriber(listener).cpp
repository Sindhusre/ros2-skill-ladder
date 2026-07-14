#include<memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgd/msg/float64.hpp"

class Batterylevel_subscriber :public rclcpp ::Node
{
public:
  Batterylevel_subscriber():Node("Batterylevel_subscriber"){
    auto topic_callback=
       [this](std_msgd::msg::Float64::UniquePtr msg)->void{
         RCLCPP_INFO(this->get_logger(),"the battery level is: %.2f",msg->data);
       };
     subscription_=
       this->create_subscription<std_msgs::msg::Float64>("batterylevel",10,topic_callback);
    private:
       rclcpp::Subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
};
int main(int argc , char *argv[]){
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared<Batterylevel_subscriber>());
  rclcpp::shutdown();
  return 0;
  
}
