#ifndef MUAN_UTILS_OFFSET_PROFILED_CONTROLLER_POT_CALIBRATION_H_
#define MUAN_UTILS_OFFSET_PROFILED_CONTROLLER_POT_CALIBRATION_H_

namespace muan {

class PotCalibration {
 public:
  PotCalibration(double units_per_index);
  ~PotCalibration();

  double Update(double enc_value, double pot_value, bool index_click);
  void Reset();

  // Getters for if it's calibrated and if the system miscalibrated after the
  // initial calibration.
  bool is_calibrated() const;
  bool index_error() const;

 private:
  double units_per_index_;

  // For averaging
  double offset_sum_;
  int average_counter_;

  int last_index_pulse_;
  bool has_index_pulse_;

  int offset_;
  bool calibrated_, index_error_;
};
}

#endif  // MUAN_UTILS_OFFSET_PROFILED_CONTROLLER_POT_CALIBRATION_H_
