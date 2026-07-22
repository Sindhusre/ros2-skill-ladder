#include "rclcpp/rclcpp.hpp"
#include "rclcpp_lifecycle/lifecycle_node.hpp"
#include<memory>
#include "std_msgs/msg/float64.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class BatteryLifeCycle:public rclcpp_lifecycle::LifecycleNode{
  public:
      BatteryLifeCycle(): LifecycleNode("battery_lifecycle"){
        RCLCPP_INFO(get_logger(),"node created");
      }
        
      CallbackReturn on_configure(const rclcpp_lifecycle::State &){
             auto topic_callback=
                   [this](std_msgs::msg::Float64::UniquePtr msg)->void{
                     state_of_charge=msg->data;
                   };
              subscription_=
                       this->create_subscription<std_msgs::msg::Float64>("batterylevel",10,topic_callback);
  
      
        RCLCPP_INFO(get_logger(),"state of charge is =%0.2f",State_of_charge);
        if(State_of_charge<30){
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
  if(State_of_charge<15){
    RCLCPP_INFO(get_logger(),"less power retun to home");
  }
  return CallbackReturn::SUCCESS;
}
CallbackReturn on_cleanup(const rclcpp_lifecycle::State&){
  RCLCPP_INFO(get_logger(),"low power navigation");
  RCLCPP_INFO(get_logger(),"turning o fthe high power_suction motors");
  return CallbackReturn::SUCCESS;
}
CallbackReturn on_shutdown(const rclcpp_lifecycle::State&){
  
  RCLCPP_INFO(get_logger(),"turning o f motors");
  motor=false;
  return CallbackReturn::SUCCESS;
}

private:
bool motor=false;
double State_of_charge=0;
rclcpp::Subscription
<std_msgs::msg::Float64>
::SharedPtr subscription_; 
};
int main(int argc,char*argv[])
{
 rclcpp::init(argc,argv);
 auto lc_node = std::make_shared<BatteryLifeCycle>();
 rclcpp::executors::SingleThreadedExecutor executor;
 executor.add_node(lc_node->get_node_base_interface());
 rclcpp::spin();
 rclcpp::shutdown();
  return 0;
}
  
 
     

      




