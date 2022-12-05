#include "rclcpp/rclcpp.hpp"
#include "settei_interfaces/srv/get_data.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>
#include <iostream>
#include "my_package/jsonload.hpp"
using namespace std::chrono_literals;

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);

//   if (argc != 3) {
//       RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "usage: add_two_ints_client X Y");
//       return 1;
//   }

  std::shared_ptr<rclcpp::Node> node = rclcpp::Node::make_shared("settei_get_data_client");
  rclcpp::Client<settei_interfaces::srv::GetData>::SharedPtr client =
    node->create_client<settei_interfaces::srv::GetData>("settei_get_data");

  auto request = std::make_shared<settei_interfaces::srv::GetData::Request>();
  request->package = "aruku";
  request->robot = "robot";
  request->branch = "master";

  while (!client->wait_for_service(1s)) {
    if (!rclcpp::ok()) {
      RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service. Exiting.");
      return 0;
    }
    RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "service not available, waiting again...");
  }

  auto result = client->async_send_request(request);
  // Wait for the result.
  if (rclcpp::spin_until_future_complete(node, result) ==
    rclcpp::FutureReturnCode::SUCCESS)
  {
    jsonloader::write("/home/zharif/iki-test/disini/src/my_package/data/",
    result.get()->filename_array,result.get()->data_array);
    // int n = result.get()->filename_array.size();
    // for (auto i = 0; i < n; i++)
    // {
    //   // RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "filename : %s ; data : %s", result.get()->filename_array,
    //   // result.get()->data_array);
    //   std::cout << result.get()->filename_array[i] << " ; " << result.get()->data_array[i] << std::endl;
    // }
  } else {
    RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_two_ints");
  }

  rclcpp::shutdown();
  return 0;
}