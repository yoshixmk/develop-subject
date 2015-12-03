#include "RobotAction.h"

namespace Strategy {

void RobotAction::moveToCenter(CvPoint aMalletCoordinate)
{
	CvPoint waiting_position;
	waiting_position.x = (FrameCoordinate::getRobotGoalLeft().x + FrameCoordinate::getRobotGoalRight().x)/2;
	waiting_position.y = (FrameCoordinate::getRobotGoalLeft().y + FrameCoordinate::getRobotGoalRight().y)/2;

	if(aMalletCoordinate.x < waiting_position.x -40){
		//ゴールから遠いと速くする
		mFrequencyX.output1000('R');
	}
	else if(aMalletCoordinate.x < waiting_position.x -10){
		//ゴール近辺ならモータの速度を落とす
		mFrequencyX.output313('R');
	}
	else if(aMalletCoordinate.x <= waiting_position.x -3){
		//ゴールに少し近づいてきたら速度を落とす
		mFrequencyX.output100('R');
	}
	else if(aMalletCoordinate.x < waiting_position.x + 3){
		//-3 ~ 3 の範囲は停止
		mFrequencyX.stop();
	}
	else if(aMalletCoordinate.x < waiting_position.x + 10){
		//ゴールに少し近づいてきたら速度を落とす
		mFrequencyX.output100('L');
	}
	else if(aMalletCoordinate.x < waiting_position.x +40){
		//ゴール近辺ならモータの速度を落とす
		mFrequencyX.output313('L');
	}
	else{
		mFrequencyX.output1000('L');
	}
}

void RobotAction::moveToHitBack(CvPoint aPredictedCoordinate, CvPoint aMalletCoordinate)
{

}

}  // namespace Strategy
