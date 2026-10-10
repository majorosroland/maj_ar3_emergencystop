#include <chrono>
#include <memory>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

using namespace std::chrono_literals;

class EmergencyStopPublisher : public rclcpp::Node {
public:
  EmergencyStopPublisher() : Node("emergency_stop_publisher"), count_(0) {
    publisher_ = this->create_publisher<std_msgs::msg::Bool>("ar3/emergency_stop", 10);
    timer_ = this->create_wall_timer(1000ms, std::bind(&EmergencyStopPublisher::timer_callback, this));
    RCLCPP_INFO(this->get_logger(), "Emergency Stop Publisher node elindult.");
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::Bool();
    // Minden 5. másodpercben vészleállítást szimulálunk (true), egyébként false
    message.data = (count_ % 5 == 0 && count_ != 0);
    
    if (message.data) {
      RCLCPP_WARN(this->get_logger(), "[KÜLDÉS] VÉSZLEÁLLÍTÁS AKTIVÁLVA! (true)");
    } else {
      RCLCPP_INFO(this->get_logger(), "[KÜLDÉS] AR3 robot állapota: Normál (false)");
    }
    
    publisher_->publish(message);
    count_++;
  }

  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<EmergencyStopPublisher>());
  rclcpp::shutdown();
  return 0;
}
