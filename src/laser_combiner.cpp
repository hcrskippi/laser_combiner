#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "sensor_msgs/LaserScan.h"

class Combiner{
public:
	Combiner(ros::NodeHandle n);
	~Combiner(){};

	void scanCallBack(sensor_msgs::LaserScan msg);
private:
	ros::Publisher leftPub;
	ros::Publisher rightPub;
};


Combiner::Combiner(ros::NodeHandle n){
	this->leftPub = n.advertise<std_msgs::LaserScan>("kerbDetectLeft", 1000);
	this->rightPub = n.advertise<std_msgs::LaserScan>("kerbDetectRight", 1000);
}


void Combiner::scanCallBack(sensor_msgs::LaserScan msg){
	if (msg.header.frame_id == "kerbDetectLeft"){
		leftPub.publish(msg);
	}else if (msg.header.frame_id == "kerbDetectRight"){
		rightPub.publish(msg);
	}
}

int main(int argc, char * argv[]){

	ros::init(argc, argv, "laser_combiner");

	ros::NodeHandle n;

	Combiner c(n);

	ros::Subscriber sub = n.subscribe("scan", 1000, &Combiner::scanCallBack, &c);
	ros::spin();

	return 0;
}
