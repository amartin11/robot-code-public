#include "c2017/subsystems/superstructure/ground_ball_intake/ground_ball_intake.h"
#include "c2017/queue_manager/queue_manager.h"

namespace c2017 {

namespace ground_ball_intake {

GroundBallIntake::GroundBallIntake()
    : status_queue_{QueueManager::GetInstance().ground_ball_intake_status_queue()} {}

GroundBallIntakeOutputProto GroundBallIntake::Update(const DriverStationStatus& robot_state) {
  GroundBallIntakeStatusProto status;
  GroundBallIntakeOutputProto output;
  double roller_voltage = 0;
  bool enable_outputs = !(robot_state.mode() == RobotMode::DISABLED ||
                          robot_state.mode() == RobotMode::ESTOP || robot_state.brownout() == true);

  if (enable_outputs) {
    switch (run_intake_) {
      case RollerGoal::INTAKE:
        roller_voltage = 12;
        break;
      case RollerGoal::OUTTAKE:
        roller_voltage = -12;
        break;
      case RollerGoal::IDLE:
        roller_voltage = 0;
        break;
    }
  } else {
    roller_voltage = 0;
    intake_up_ = true;
  }

  output->set_roller_voltage(roller_voltage);
  output->set_intake_up(intake_up_);

  status->set_running(run_intake_);
  status->set_is_intake_up(intake_up_);

  status_queue_.WriteMessage(status);

  return output;
}

void GroundBallIntake::set_goal(GroundBallIntakeGoalProto goal) {
  intake_up_ = goal->intake_up();
  run_intake_ = goal->run_intake();
}

}  // ground_ball_intake

}  // c2017
