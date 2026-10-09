#include <memory>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/bool.hpp"

class BatteryAlarmNode : public rclcpp::Node {
public:
  BatteryAlarmNode() : Node("battery_alarm_node") {
    subscription_ = this->create_subscription<std_msgs::msg::Float32>(
      "battery_level", 10,
      std::bind(&BatteryAlarmNode::battery_callback, this, std::placeholders::_1));

    alarm_publisher_ = this->create_publisher<std_msgs::msg::Bool>("battery_alarm", 10);

    RCLCPP_INFO(this->get_logger(), "Battery Alarm Node figyel.");
  }

private:
  void battery_callback(const std_msgs::msg::Float32::SharedPtr msg) const {
    auto alarm_msg = std_msgs::msg::Bool();

    if (msg->data <= 20.0f) {
      alarm_msg.data = true;
      RCLCPP_WARN(this->get_logger(), "FIGYELEM! Kritikus akkumulatorszint: %.1f%%!", msg->data);
    } else {
      alarm_msg.data = false;
      RCLCPP_INFO(this->get_logger(), "Akkumulatorszint rendben: %.1f%%", msg->data);
    }

    alarm_publisher_->publish(alarm_msg);
  }

  rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr subscription_;
  rclcpp::Publisher<std_msgs::msg::Bool>::SharedPtr alarm_publisher_;
};

int main(int argc, char * argv[]) {
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<BatteryAlarmNode>());
  rclcpp::shutdown();
  return 0;
}