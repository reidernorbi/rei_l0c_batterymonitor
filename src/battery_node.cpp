#include <chrono>
#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class BatteryNode : public rclcpp::Node {
public:
  BatteryNode() : Node("battery_node"), battery_level_(100.0f) {
    publisher_ = this->create_publisher<std_msgs::msg::Float32>("battery_level", 10);
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&BatteryNode::timer_callback, this));

    RCLCPP_INFO(this->get_logger(), "Battery Node elindult. Kezdo toltottseg: %.1f%%", battery_level_);
  }

private:
  void timer_callback() {
    auto message = std_msgs::msg::Float32();
    message.data = battery_level_;
    publisher_->publish(message);

    RCLCPP_INFO(this->get_logger(), "Akkumulator szint: %.1f%%", battery_level_);

    if (battery_level_ > 0.0f) {
      battery_level_ -= 5.0f;
    } else {
      battery_level_ = 100.0f;
      RCLCPP_INFO(this->get_logger(), "Akkumulator ujratoltve!");
    }
  }

  float battery_level_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr publisher_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BatteryNode>());
  rclcpp::shutdown();
  return 0;
}