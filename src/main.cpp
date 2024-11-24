#include <iostream>
#include <glog/logging.h>

int main(int argc, char *argv[])
{
   google::InitGoogleLogging(argv[0]);
   google::SetLogFilenameExtension(".log");
   // FLAGS_logtostderr = 1;
   FLAGS_log_dir = ".";
   FLAGS_timestamp_in_logfile_name = false;
   FLAGS_logfile_mode = 0;
   LOG(INFO) << "Found 0 cookies";
   // std::cout << "Hello to the APOD API" << std::endl;
   // FLAGS_logto = 1;
   LOG(INFO) << "Found 1 cookies";
   return 0;
}