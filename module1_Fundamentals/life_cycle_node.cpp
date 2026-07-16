#include "rclcpp/rclcpp.hpp"
#inlcude "rclcpp_lifecycle/lifecycle_node.hpp"
#include<memory>
#include "std_msgs/msg/float64.hpp"

using CallbackReturn = rclcpp_lifecycle::node_interfaces::LifecycleNodeInterface::CallbackReturn;

class BatteryLifeCycle ():public rclcpp_lifecycle::LifeCycleNode,public rclcpp::Node{
  public:
      BatteryLifeCycle(): LifecycleNode("battery_lifecycle"){
        auto topic_callback=
                   [this](std_msgs::msg::Float64::UniquePtr msg)->void{
                     State_of_charge=msg->data;
                   };
              subscription_=
                       this->create_subscription<std_msgs::msg::Float64>::SharedPtr subscription_;
  
      }
      CallbackReturn on_configure(const rclcpp_lifecycle::State &){
        RCLCPP_INFO(get_logger(),"state of charge is =%0.2f",State_of_charge);
        if(state_of_charge<30){
          RCL_INFO(get_logger(),"charge is less cannot opearte now");
          return CallbackReturn::FAILURE;}
        return CallbackReturn::SUCCESS;
      }
 
     

      


}

