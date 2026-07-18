#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include<memory>
#include "std_msgs/msg/float64.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class BatteryLifeCycle:public rclcpp_lifecycle::LifecycleNode{
  public:
      BatteryLifeCycle(): LifecycleNode("battery_lifecycle"){
        RCL_INFO(gte_logger(),"node created");
      }
        
      CallbackReturn on_configure(const rclcpp_lifecycle::State &){
             auto topic_callback=
                   [this](std_msgs::msg::Float64::UniquePtr msg)->void{
                     state_of_charge=msg->data;
                   };
              subscription_=
                       this->create_subscription<std_msgs::msg::Float64>("battery_level",10,topic_callback);
  
      
        RCLCPP_INFO(get_logger(),"state of charge is =%0.2f",State_of_charge);
        if(state_of_charge<30){
          RCL_INFO(get_logger(),"charge is less cannot opearte now");
          return CallbackReturn::FAILURE;}
        return CallbackReturn::SUCCESS;
     }
CallbackReturn on_acitive(const rclcpp_lifecycle:: State &){
  motor=true;
  RCLCPP_INFO(get_logger(),"Motor Turned On");
  RCLCPP_INFO(get_logger(),"state of charge is =%0.2f",State_of_charge);
  return CallbackReturn::SUCCESS;
  
}
CallbackReturn on_deactivate(const rclcpp_lifecycle::State&){
  if(state_of_charge<15){
    RCLCPP_INFO(get_logger(),"less power retun to home");
  }
}
CallbackReturn on_cleanup(const rclcpp_lifecycle::State&){
  RCLCPP_INFO(get_logger(),"low power navigation");
  RCLCPP_INFO(get_logger(),"turning o fthe high power_suction motors");
  
}
CallbackReturn on_cleanup(const rclcpp_lifecycle::State&){
  
  RCLCPP_INFO(get_logger(),"turning o f motors");
  motor=false;
  
}

private:
bool motor=false;
double state_of_charge=0;
};
int main(int argc,char*argv[])
{
 rclcpp::init(argc,argv);
rclcpp::spin(
  std::make_shared<BatteryLifeCycle>());
  rclcpp::shutdown();
  return 0;
}
  
 
     

      




