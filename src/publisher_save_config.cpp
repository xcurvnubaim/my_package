// Copyright 2016 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "my_package/jsonload.hpp"
#include "settei_interfaces/msg/write_data.hpp"


using namespace std::chrono_literals;

/* This example creates a subclass of Node and uses std::bind() to register a
 * member function as a callback from the timer. */

class MinimalPublisher : public rclcpp::Node
{
public:
  MinimalPublisher()
  : Node("minimal_publisher"), count_(0)
  {
    publisher_ = this->create_publisher<settei_interfaces::msg::WriteData>("topic", 10);
    timer_ = this-> create_wall_timer(
      500ms, std::bind(&MinimalPublisher::timer_callback, this));
  }

private:
  void timer_callback()
  {
    auto message = settei_interfaces::msg::WriteData();
    message.package = "aruku";
    message.robot = "robot";
    message.branch = "master";

    jsonloader::get("/home/zharif/iki-test/disini/src/my_package/data/",
    message.filename_array,message.data_array);
    
    RCLCPP_INFO(this->get_logger(), "Publishing: ''");
    publisher_->publish(message);
    rclcpp::shutdown();
  }
  rclcpp::TimerBase::SharedPtr timer_;
  rclcpp::Publisher<settei_interfaces::msg::WriteData>::SharedPtr publisher_;
  size_t count_;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalPublisher>());
  rclcpp::shutdown();
  return 0;
}
