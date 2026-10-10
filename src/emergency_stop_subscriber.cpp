#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

class EmergencyStopSubscriber : public rclcpp::Node {
public:
  EmergencyStopSubscriber() : Node("emergency_stop_subscriber") {
    subscription_ = this->create_subscription<std_msgs::msg::Bool>(
      "ar3/emergency_stop", 10,
      std::bind(&EmergencyStopSubscriber::topic_callback, this, std::placeholders::_1));
    RCLCPP_INFO(this->get_logger(), "Emergency Stop Subscriber node elindult, figyeli a jeleket.");
  }

private:
  void topic_callback(const std_msgs::msg::Bool::SharedPtr msg) const {
    if (msg->data) {
      RCLCPP_ERROR(this->get_logger(), "[FELDOLGOZÁS] FIGYELEM: Vészleállító jel fogadva! AR3 robot azonnal megállítva!");
    } else {
      RCLCPP_INFO(this->get_logger(), "[FELDOLGOZÁS] Vett állapot: Rendben, a robot futhat.");
    }
  }

  rclcpp::Subscription<std_msgs::msg::Bool>::SharedPtr subscription_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EmergencyStopSubscriber>());
  rclcpp::shutdown();
  return 0;
}
