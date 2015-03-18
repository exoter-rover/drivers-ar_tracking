#include <iostream>
#include <sstream>
#include <time.h>
#include <math.h>
#include <base/logging.h>
#include "DTrackSDK.hpp"
#include "ArtDriver.hpp"

using namespace std;
using namespace artracking;

static DTrackSDK* dt = NULL;

ARTDriver::ARTDriver()
{

}

bool ARTDriver::connect (const std::string& server_host, unsigned short server_port, unsigned short data_port)
{
	std::cout << "Connecting to ART..." 
                  << std::endl;
    dt = new DTrackSDK(server_host,  server_port,data_port, DTrackSDK::SYS_DTRACK_UNKNOWN);
    
    // This is in case you only need the listening mode: Uncomment line below, comment line above
    // dt = new DTrackSDK( server_port);

    std::cout << "Connection stablished" 
                  << std::endl;

    //I have no clue of how to check if this shit is connected
	return true;
}
bool ARTDriver::isConnected()
{
	return false;
}
void ARTDriver::disconnect()
{
	LOG_INFO_S << "disconnecting";
	delete dt;

}
bool ARTDriver::getFrame( const base::Time& timeout)
{
	bool error = dt->receive();
	return error;
}
base::Time ARTDriver::getTimestamp()
{
	return base::Time::now();
}

Eigen::Affine3d ARTDriver::getSegmentTransform( int numBody)
{
	DTrack_Body_Type_d body;
	Eigen::Affine3d result;
	if (numBody>dt->getNumBody()){
		cout << "Error: body number too high"<< endl;
		Eigen::Vector3d trans_m( 0,0,0);
		result = Eigen::Translation3d(trans_m)*
		Eigen::Quaterniond(1,0,0,0);
	}else{
		body = *dt->getBody(numBody);
		Eigen::Vector3d trans_m( body.loc[0],body.loc[1],body.loc[2]);
		Eigen::Quaterniond q = this->r_to_q(body.rot);
		// ART gives data in mm, we want it in metres
		result = Eigen::Translation3d(trans_m * 1e-3)*q;
		
	}

	return result;
}

/**
 * 	\brief Quaternion from Rotation matrix
 *
 * 	@return Quaternion
 */

Eigen::Quaterniond ARTDriver::r_to_q( double r[])
 {
	 /*We assume that the rotation data from ART is 
	   column-wise as they say, so the second element is
	   second row - first column
	 */
 	Eigen::Matrix3d m(r);
 	Eigen::Quaterniond q = Eigen::Quaterniond(m);
  	return q;
 }

/**
 * 	\brief Prints error messages to console
 *
 */
bool ARTDriver::error_to_console()
{
	if (dt->getLastDataError() == DTrackSDK::ERR_TIMEOUT) {
		cout << "--- timeout while waiting for tracking data" << endl;
		return false;
	}

	if (dt->getLastDataError() == DTrackSDK::ERR_NET) {
		cout << "--- error while receiving tracking data" << endl;
		return false;
	}

	if (dt->getLastDataError() == DTrackSDK::ERR_PARSE){
		cout << "--- error while parsing tracking data" << endl;
		return false;
	}

	return true;
}
/**
 * 	\brief Prints current tracking data to console.
 */

void ARTDriver::output_to_console()
{
	cout.precision(3);
	cout.setf(ios::fixed, ios::floatfield);

	cout << endl << "frame " << dt->getFrameCounter() << " ts " << dt->getTimeStamp()
	     << " nbod " << dt->getNumBody() << " nfly " << dt->getNumFlyStick()
	     << " nmea " << dt->getNumMeaTool() << " nmearef " << dt->getNumMeaRef() 
			 << " nhand " << dt->getNumHand() << " nmar " << dt->getNumMarker() 
			 << " nhuman " << dt->getNumHuman() 
			 << endl;

	// bodies:
	DTrack_Body_Type_d body;
	for(int i=0; i<dt->getNumBody(); i++){
		body = *dt->getBody(i);

		if(body.quality < 0){
			cout << "bod " << body.id << " not tracked" << endl;
		}else{
			cout << "bod " << body.id << " qu " << body.quality
			     << " loc " << body.loc[0] << " " << body.loc[1] << " " << body.loc[2]
			     << " rot " << body.rot[0] << " " << body.rot[1] << " " << body.rot[2]
			     << " " << body.rot[3] << " " << body.rot[4] << " " << body.rot[5]
			     << " " << body.rot[6] << " " << body.rot[7] << " " << body.rot[8] << endl;
		}
	}

	// A.R.T. Flysticks:
	DTrack_FlyStick_Type_d flystick;
	for(int i=0; i<dt->getNumFlyStick(); i++){
		flystick = *dt->getFlyStick(i);

		if(flystick.quality < 0){
			cout << "fly " << flystick.id << " not tracked" << endl;
		}else{
			cout << "flystick " << flystick.id << " qu " << flystick.quality
			     << " loc " << flystick.loc[0] << " " << flystick.loc[1] << " " << flystick.loc[2]
			     << " rot " << flystick.rot[0] << " " << flystick.rot[1] << " " << flystick.rot[2]
			     << " " << flystick.rot[3] << " " << flystick.rot[4] << " " << flystick.rot[5]
			     << " " << flystick.rot[6] << " " << flystick.rot[7] << " " << flystick.rot[8] << endl;
		}

		cout << "      btn";
		for(int j=0; j<flystick.num_button; j++){
			cout << " " << flystick.button[j];
		}

		cout << " joy";
		for(int j=0; j<flystick.num_joystick; j++){
			cout << " " << flystick.joystick[j];
		}

		cout << endl;
	}

	// measurement tools:
	DTrack_MeaTool_Type_d meatool;
	for(int i=0; i<dt->getNumMeaTool(); i++){
		meatool = *dt->getMeaTool(i);

		if(meatool.quality < 0){
			cout << "mea " << meatool.id << " not tracked" << endl;
		}else{
			cout << "mea " << meatool.id << " qu " << meatool.quality
			     << " loc " << meatool.loc[0] << " " << meatool.loc[1] << " " << meatool.loc[2]
			     << " rot " << meatool.rot[0] << " " << meatool.rot[1] << " " << meatool.rot[2]
			     << " " << meatool.rot[3] << " " << meatool.rot[4] << " " << meatool.rot[5]
			     << " " << meatool.rot[6] << " " << meatool.rot[7] << " " << meatool.rot[8] << endl;
		}

		if (meatool.tipradius) {
			cout << "      radius " << meatool.tipradius << endl;
		}

		if (meatool.num_button) {
			cout << "      btn";
			for(int j=0; j<meatool.num_button; j++){
				cout << " " << meatool.button[j];
			}
			cout << endl;
		}
	}
	
	// measurement references:
	DTrack_MeaRef_Type_d mearef;
	for(int i=0; i<dt->getNumMeaRef(); i++){
		mearef = *dt->getMeaRef(i);

		if(mearef.quality < 0){
			cout << "mearef " << mearef.id << " not tracked" << endl;
		}else{
			cout << "mearef " << mearef.id << " qu " << mearef.quality
				<< " loc " << mearef.loc[0] << " " << mearef.loc[1] << " " << mearef.loc[2]
			<< " rot " << mearef.rot[0] << " " << mearef.rot[1] << " " << mearef.rot[2]
			<< " " << mearef.rot[3] << " " << mearef.rot[4] << " " << mearef.rot[5]
			<< " " << mearef.rot[6] << " " << mearef.rot[7] << " " << mearef.rot[8] << endl;
		}
	}

	// markers:
	DTrack_Marker_Type_d marker;
	for(int i=0; i<dt->getNumMarker(); i++){
		marker = *dt->getMarker(i);

		cout << "mar " << marker.id << " qu " << marker.quality
		     << " loc " << marker.loc[0] << " " << marker.loc[1] << " " << marker.loc[2] << endl;
	}

	// A.R.T. Fingertracking hands:
	DTrack_Hand_Type_d hand;
	for(int i=0; i<dt->getNumHand(); i++){
		hand = *dt->getHand(i);

		if(hand.quality < 0){
			cout << "hand " << hand.id << " not tracked" << endl;
		}else{
			cout << "hand " << hand.id << " qu " << hand.quality
			     << " lr " << ((hand.lr == 0) ? "left" : "right") << " nf " << hand.nfinger
			     << " loc " << hand.loc[0] << " " << hand.loc[1] << " " << hand.loc[2]
			     << " rot " << hand.rot[0] << " " << hand.rot[1] << " " << hand.rot[2]
			     << " " << hand.rot[3] << " " << hand.rot[4] << " " << hand.rot[5]
			     << " " << hand.rot[6] << " " << hand.rot[7] << " " << hand.rot[8] << endl;

			for(int j=0; j<hand.nfinger; j++){
				cout << "       fi " << j
				     << " loc " << hand.finger[j].loc[0] << " " << hand.finger[j].loc[1] << " " << hand.finger[j].loc[2]
				     << " rot " << hand.finger[j].rot[0] << " " << hand.finger[j].rot[1] << " " << hand.finger[j].rot[2]
				     << " " << hand.finger[j].rot[3] << " " << hand.finger[j].rot[4] << " " << hand.finger[j].rot[5]
				     << " " << hand.finger[j].rot[6] << " " << hand.finger[j].rot[7] << " " << hand.finger[j].rot[8] << endl;
				cout << "       fi " << j
				     << " tip " << hand.finger[j].radiustip
				     << " pha " << hand.finger[j].lengthphalanx[0] << " " << hand.finger[j].lengthphalanx[1]
				     << " " << hand.finger[j].lengthphalanx[2]
				     << " ang " << hand.finger[j].anglephalanx[0] << " " << hand.finger[j].anglephalanx[1] << endl;
			}
		}
	}

	// A.R.T human model (6dj)
	DTrack_Human_Type human;

	if (dt->getNumHuman() < 1) {
		cout << "no human model data" << endl;
	}

	for(int i=0; i<dt->getNumHuman(); i++){
		human = *dt->getHuman(i);
		cout << "human " << human.id << " num joints " << human.num_joints << endl;
		for (int j=0; j<human.num_joints; j++){
			if(human.joint[j].quality<0){
				cout << "joint " << human.joint[j].id << " not tracked" << endl;
			}else{
				cout << "joint " << human.joint[j].id << " qu " << human.joint[j].quality
				     << " loc "  << human.joint[j].loc[0] << " " << human.joint[j].loc[1] << " " << human.joint[j].loc[2]
				     << " ang "  << human.joint[j].ang[0] << " " << human.joint[j].ang[1] << " " << human.joint[j].ang[2]
				     << " rot "  << human.joint[j].rot[0] << " " << human.joint[j].rot[1] << " " << human.joint[j].rot[2]
				     << " "      << human.joint[j].rot[3] << " " << human.joint[j].rot[4] << " " << human.joint[j].rot[5]
				     << " "      << human.joint[j].rot[6] << " " << human.joint[j].rot[7] << " " << human.joint[j].rot[8]
				     << endl;
			}
		}
		cout << endl;
	}

	// A.R.T inertial bodies(6di)
	DTrack_Inertial_Type_d inertial;

	if (dt->getNumInertial() < 1) {
		cout << "no inertial body data" << endl;
	}

	for(int i=0; i<dt->getNumInertial(); i++){
		inertial = *dt->getInertial(i);
		cout << " inertial body " << inertial.id << " st " << inertial.st << " error " << inertial.error << endl;
		if(inertial.st > 0){
			cout << " loc " << inertial.loc[0] << " " << inertial.loc[1] << " " << inertial.loc[2]
			     << " rot " << inertial.rot[0] << " " << inertial.rot[1] << " " << inertial.rot[2]
			     << " " << inertial.rot[3] << " " << inertial.rot[4] << " " << inertial.rot[5]
			     << " " << inertial.rot[6] << " " << inertial.rot[7] << " " << inertial.rot[8] << endl;
		}
	}
}