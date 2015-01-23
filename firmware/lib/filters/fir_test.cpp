#include <cmath>

#include "hal.h"
#include "fir.hpp"
#include "array_len.hpp"

using namespace filters;

#define FILTER_LEN    257
#define ROUNDS        1000

static const float taps[FILTER_LEN] = {1.6620901939545977e-20,-7.6371804880182026e-08,-3.4941132298627053e-07,-8.8005049292405602e-07,-1.7211790463989018e-06,-2.9159007226553513e-06,-4.4958696889807470e-06,-6.4797295635798946e-06,-8.8716806203592569e-06,-1.1660196832963265e-05,-1.4816920156590641e-05,-1.8295766494702548e-05,-2.2032261767890304e-05,-2.5943138098227791e-05,-2.9926230126875453e-05,-3.3860684197861701e-05,-3.7607529520755634e-05,-4.1010596760315821e-05,-4.3897860450670123e-05,-4.6083172492217273e-05,-4.7368448576889932e-05,-4.7546258429065347e-05,-4.6402888983720914e-05,-4.3721811380237341e-05,-3.9287602703552693e-05,-3.2890227885218337e-05,-2.4329719963134266e-05,-1.3421168659988325e-05,5.7405106664958362e-20,1.6072546713985503e-05,3.4903790947282687e-05,5.6563923862995580e-05,8.1080353993456811e-05,1.0843219206435606e-04,1.3854494318366051e-04,1.7128558829426765e-04,2.0645813492592424e-04,2.4379970273002982e-04,2.8297738754190505e-04,3.2358599128201604e-04,3.6514652310870588e-04,4.0710603934712708e-04,4.4883840018883348e-04,4.8964651068672538e-04,5.2876572590321302e-04,5.6536885676905513e-04,5.9857236919924617e-04,6.2744447495788336e-04,6.5101438667625189e-04,6.6828308627009392e-04,6.7823578137904406e-04,6.7985558416694403e-04,6.7213829606771469e-04,6.5410876413807273e-04,6.2483793590217829e-04,5.8346078731119633e-04,5.2919524023309350e-04,4.6136078890413046e-04,3.7939820322208107e-04,2.8288841713219881e-04,1.7157141701318324e-04,4.5364475226961076e-05,-9.5620758656878024e-05,-2.5106224347837269e-04,-4.2041318374685943e-04,-6.0288951499387622e-04,-7.9745950642973185e-04,-1.0028360411524773e-03,-1.2174709700047970e-03,-1.4395533362403512e-03,-1.6670101322233677e-03,-1.8975102575495839e-03,-2.1284723188728094e-03,-2.3570759221911430e-03,-2.5802769232541323e-03,-2.7948250062763691e-03,-2.9972866177558899e-03,-3.1840703450143337e-03,-3.3514557871967554e-03,-3.4956254530698061e-03,-3.6127006169408560e-03,-3.6987783387303352e-03,-3.7499715108424425e-03,-3.7624510005116463e-03,-3.7324891891330481e-03,-3.6565037444233894e-03,-3.5311034880578518e-03,-3.3531319350004196e-03,-3.1197138596326113e-03,-2.8282960411161184e-03,-2.4766908027231693e-03,-2.0631148945540190e-03,-1.5862259315326810e-03,-1.0451561538502574e-03,-4.3954170541837811e-04,2.3045166744850576e-04,9.6410827245563269e-04,1.7601469298824668e-03,2.6167107280343771e-03,3.5313628613948822e-03,4.5010880567133427e-03,5.5223000235855579e-03,6.5908567048609257e-03,7.7020782046020031e-03,8.8507737964391708e-03,1.0031275451183319e-02,1.1237474158406258e-02,1.2462861835956573e-02,1.3700583949685097e-02,1.4943488873541355e-02,1.6184186562895775e-02,1.7415108159184456e-02,1.8628573045134544e-02,1.9816849380731583e-02,2.0972229540348053e-02,2.2087089717388153e-02,2.3153966292738914e-02,2.4165621027350426e-02,2.5115108117461205e-02,2.5995837524533272e-02,2.6801643893122673e-02,2.7526831254363060e-02,2.8166245669126511e-02,2.8715308755636215e-02,2.9170069843530655e-02,2.9527241364121437e-02,2.9784236103296280e-02,2.9939185827970505e-02,2.9990961775183678e-02,2.9939185827970505e-02,2.9784236103296280e-02,2.9527241364121437e-02,2.9170069843530655e-02,2.8715308755636215e-02,2.8166245669126511e-02,2.7526831254363060e-02,2.6801643893122673e-02,2.5995837524533272e-02,2.5115108117461205e-02,2.4165621027350426e-02,2.3153966292738914e-02,2.2087089717388153e-02,2.0972229540348053e-02,1.9816849380731583e-02,1.8628573045134544e-02,1.7415108159184456e-02,1.6184186562895775e-02,1.4943488873541355e-02,1.3700583949685097e-02,1.2462861835956573e-02,1.1237474158406258e-02,1.0031275451183319e-02,8.8507737964391708e-03,7.7020782046020031e-03,6.5908567048609257e-03,5.5223000235855579e-03,4.5010880567133427e-03,3.5313628613948822e-03,2.6167107280343771e-03,1.7601469298824668e-03,9.6410827245563269e-04,2.3045166744850576e-04,-4.3954170541837811e-04,-1.0451561538502574e-03,-1.5862259315326810e-03,-2.0631148945540190e-03,-2.4766908027231693e-03,-2.8282960411161184e-03,-3.1197138596326113e-03,-3.3531319350004196e-03,-3.5311034880578518e-03,-3.6565037444233894e-03,-3.7324891891330481e-03,-3.7624510005116463e-03,-3.7499715108424425e-03,-3.6987783387303352e-03,-3.6127006169408560e-03,-3.4956254530698061e-03,-3.3514557871967554e-03,-3.1840703450143337e-03,-2.9972866177558899e-03,-2.7948250062763691e-03,-2.5802769232541323e-03,-2.3570759221911430e-03,-2.1284723188728094e-03,-1.8975102575495839e-03,-1.6670101322233677e-03,-1.4395533362403512e-03,-1.2174709700047970e-03,-1.0028360411524773e-03,-7.9745950642973185e-04,-6.0288951499387622e-04,-4.2041318374685943e-04,-2.5106224347837269e-04,-9.5620758656878024e-05,4.5364475226961076e-05,1.7157141701318324e-04,2.8288841713219881e-04,3.7939820322208107e-04,4.6136078890413046e-04,5.2919524023309350e-04,5.8346078731119633e-04,6.2483793590217829e-04,6.5410876413807273e-04,6.7213829606771469e-04,6.7985558416694403e-04,6.7823578137904406e-04,6.6828308627009392e-04,6.5101438667625189e-04,6.2744447495788336e-04,5.9857236919924617e-04,5.6536885676905513e-04,5.2876572590321302e-04,4.8964651068672538e-04,4.4883840018883348e-04,4.0710603934712708e-04,3.6514652310870588e-04,3.2358599128201604e-04,2.8297738754190505e-04,2.4379970273002982e-04,2.0645813492592424e-04,1.7128558829426765e-04,1.3854494318366051e-04,1.0843219206435606e-04,8.1080353993456811e-05,5.6563923862995580e-05,3.4903790947282687e-05,1.6072546713985503e-05,5.7405106664958362e-20,-1.3421168659988325e-05,-2.4329719963134266e-05,-3.2890227885218337e-05,-3.9287602703552693e-05,-4.3721811380237341e-05,-4.6402888983720914e-05,-4.7546258429065347e-05,-4.7368448576889932e-05,-4.6083172492217273e-05,-4.3897860450670123e-05,-4.1010596760315821e-05,-3.7607529520755634e-05,-3.3860684197861701e-05,-2.9926230126875453e-05,-2.5943138098227791e-05,-2.2032261767890304e-05,-1.8295766494702548e-05,-1.4816920156590641e-05,-1.1660196832963265e-05,-8.8716806203592569e-06,-6.4797295635798946e-06,-4.4958696889807470e-06,-2.9159007226553513e-06,-1.7211790463989018e-06,-8.8005049292405602e-07,-3.4941132298627053e-07,-7.6371804880182026e-08,1.6620901939545977e-20};

static FIR<float, float, FILTER_LEN> fir_ref(taps, ArrayLen(taps));
static FIR<float, float, FILTER_LEN> fir(taps, ArrayLen(taps));

static int8_t sample = 0;
volatile float filter1;
volatile float filter2;

static uint8_t N = 0;

time_measurement_t tmp;
time_measurement_t tmp_ref;

/**
 *
 */
void firTest(void){

  while(true){
    chTMObjectInit(&tmp);
    chTMObjectInit(&tmp_ref);

    for (size_t i=0; i<ROUNDS; i++) {
      chTMStartMeasurementX(&tmp);
      filter1 = fir.update(sample);
      chTMStopMeasurementX(&tmp);

      chTMStartMeasurementX(&tmp_ref);
      filter2 = fir_ref.update_reference(sample);
      chTMStopMeasurementX(&tmp_ref);

      osalDbgAssert(fabsf(filter1-filter2) < 0.001f, "FIR test failed");
      sample += 1;
      N++;
    }
    __asm("BKPT #0\n");
  }
}
