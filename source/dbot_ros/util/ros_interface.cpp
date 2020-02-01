/*
 * This is part of the Bayesian Object Tracking (bot),
 * (https://github.com/bayesian-object-tracking)
 *
 * Copyright (c) 2015 Max Planck Society,
 * 				 Autonomous Motion Department,
 * 			     Institute for Intelligent Systems
 *
 * This Source Code Form is subject to the terms of the GNU General Public
 * License License (GNU GPL). A copy of the license can be found in the LICENSE
 * file distributed with this source code.
 */

/**
 * \file ros_interface.h
 * \date 2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 */

#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <dbot_ros/util/ros_interface.h>
#include <dbot_ros_msgs/ObjectState.h>

void ri::publish_marker(const geometry_msgs::PoseStamped& pose_stamped,
                        const std::string& object_model_path,
                        const ros::Publisher& pub,
                        const int& marker_id,
                        const float& r,
                        const float& g,
                        const float& b,
                        const float& a,
                        const std::string& ns)
{
    visualization_msgs::Marker marker, arrmarker;

    marker.pose = pose_stamped.pose;

    marker.header.frame_id = pose_stamped.header.frame_id;
    marker.header.stamp    = pose_stamped.header.stamp;
    marker.ns              = ns;
    marker.id              = marker_id;

    marker.mesh_resource = object_model_path;
    marker.scale.x       = 1.0;
    marker.scale.y       = 1.0;
    marker.scale.z       = 1.0;
    marker.color.r       = r;
    marker.color.g       = g;
    marker.color.b       = b;
    marker.color.a       = a;

    marker.type   = visualization_msgs::Marker::MESH_RESOURCE;
    marker.action = visualization_msgs::Marker::ADD;

    pub.publish(marker);




    arrmarker.header.frame_id = pose_stamped.header.frame_id;
    arrmarker.header.stamp    = pose_stamped.header.stamp;
    arrmarker.ns              = ns + "_orientation_arrows";;
    arrmarker.id              = marker_id;


    arrmarker.type = visualization_msgs::Marker::ARROW;
    arrmarker.action = visualization_msgs::Marker::ADD;
    arrmarker.scale.x = .01;
    arrmarker.scale.y = .02;
    arrmarker.scale.z = 0;
    arrmarker.color.r = 0;
    arrmarker.color.b = 0;
    arrmarker.color.g = 1;
    arrmarker.color.a = 1;

    //// 45deg in each direction
    //double angle = 0.79; // ~45deg
	//tf2::Quaternion marker_rot, arrow_rot;
	//arrow_rot.setRPY(0, -angle, angle);
	//tf2::fromMsg(marker.pose.orientation, marker_rot);
	//arrow_rot = arrow_rot * marker_rot;
	//arrow_rot.normalize();

    //marker.pose.orientation = tf2::toMsg(arrow_rot);

    //pub.publish(marker);

	// 45deg in each direction
	tf2::Quaternion marker_rot;
	tf2::Vector3 vec(0.2,0.2,0.2);
	tf2::Vector3 start_point, end_point;

	tf2::fromMsg(marker.pose.orientation, marker_rot);
	tf2::fromMsg(marker.pose.position, start_point);
	tf2::Transform trans(marker_rot);

	vec = trans * vec;
	end_point = start_point + vec;

	geometry_msgs::Point gm_end;
	tf2::toMsg(end_point, gm_end);

	arrmarker.points.clear();
	arrmarker.points.push_back(marker.pose.position);
	arrmarker.points.push_back(gm_end);

    pub.publish(arrmarker);

}
