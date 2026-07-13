//# This publisher, publish the percentage of battety level at every one minute 
#incldue<chrono>
#include<memory>
#include<string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float64.hpp"

using namespace std::chrono_literals;

class Battery_level:public rclcpp::Node
{
public:
  Battery_level():Node("Battery_level"),count(0){
    publisher_=this->create_publisher<std_msgs::msg::Float64>("Battreylevel",10);
    auto timer_callback=
         [this]()->void{
           auto number = std_msgs::msg::Float64();
           number.data=100.00-(this->count++);
           RCLCPP_INFO(this->get_logger(),"publishing: %.2f",number.data);
           this->publisher_->publish(number);
         };
    timer_ =this->create_wall_timer(1s,timer_callback);
  }
private:
rclcpp::TimerBase::SharedPtr timer_;
rclcpp::Publisher<std_msgs::msg::Float64>::sharedPtr publisher_;
size_t count;
};
int main(int argc,char*argv[])
{
  rclcpp::init(argc,argv);
  rclcpp::spin(std::make_shared< Battery_level>());
  rclcpp::shutdown();
  return 0;
}
