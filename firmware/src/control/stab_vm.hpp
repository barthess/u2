#ifndef STAB_VM_HPP_
#define STAB_VM_HPP_

#include "mavlink_local.hpp"
#include "stabilizer/stabilizer.hpp"

namespace control {

class StabVM {
public:
  void start(void);
  void stop(void);
  void update(float dT);
private:
  void pid_pool_start(void);
  void scale_pool_start(void);
  void exec(void);
  void compile(const uint8_t *bytecode);
  void destroy(void);
  bool ready = false;
  time_measurement_t exec_tmo;
};

} /* namespace */

#endif /* STAB_VM_HPP_ */
