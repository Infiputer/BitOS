#include "math.h"

double sinLookup[] = {0, 0.04997916927067833, 0.09983341664682815, 0.14943813247359924, 0.19866933079506122, 0.24740395925452294, 0.29552020666133955, 0.34289780745545134, 0.38941834230865047, 0.4349655341112302, 0.47942553860420295, 0.5226872289306591, 0.5646424733950354, 0.6051864057360395, 0.6442176872376911, 0.6816387600233342, 0.7173560908995229, 0.7512804051402928, 0.7833269096274835, 0.813415504789374, 0.8414709848078966, 0.8674232255940171, 0.8912073600614355, 0.9127639402605212, 0.9320390859672265, 0.9489846193555863, 0.9635581854171931, 0.9757233578266592, 0.9854497299884603, 0.9927129910375886, 0.9974949866040544, 0.999783764189357, 0.9995736030415051, 0.9968650284539188, 0.9916648104524685, 0.9839859468739367, 0.9738476308781949, 0.9612752029752997, 0.9463000876874141, 0.9289597150038689, 0.9092974268256814, 0.8873623686333751, 0.8632093666488735, 0.8368987907984975, 0.8084964038195901, 0.7780731968879212, 0.7457052121767203, 0.7114733527908447, 0.6754631805511513, 0.6377647021345043, 0.5984721441039572, 0.5576837173914178, 0.5155013718214653, 0.4720305412898838, 0.4273798802338314, 0.38166099205233334, 0.33498815015590677, 0.28747801234254655, 0.23924932921398456, 0.19042264736102968, 0.14112000805986985, 0.09146464223243984, 0.0415806624332936, -0.00840724736714551, -0.05837414342757654, -0.10819513453010485, -0.15774569414324469, -0.20690197167339586, -0.2555411020268274, -0.3035415127084251, -0.3507832276896157, -0.3971481672859557, -0.4425204432948481, -0.48678664865569515, -0.5298361409084889, -0.5715613187423394, -0.6118578909427147, -0.650625137065163, -0.6877661591839695, -0.7231881240865079, -0.7568024953079242, -0.7885252544261911, -0.8182771110644067, -0.8459837010754427, -0.8715757724135846, -0.8949893582285804, -0.916165936749452, -0.9350525775584465, -0.9516020738895136, -0.9657730606206367, -0.9775301176650953, -0.9868438585032353, -0.9936910036334635, -0.9980544387588789, -0.9999232575641008, -0.9992927889753783, -0.9961646088358415, -0.9905465359667145, -0.9824526126243343, -0.971903069401823, -0.9589242746631412, -0.9435486686359098, -0.9258146823277361, -0.905766641468709, -0.8834546557201581, -0.8589344934265974, -0.8322674422239071, -0.8035201558521622, -0.7727644875559945, -0.7400773104889021, -0.7055403255704, -0.6692398572762706, -0.6312666378723305, -0.5917155806310194, -0.550685542597648, -0.508279077499269, -0.46460217941376836, -0.41976401783987094, -0.3738766648302484, -0.32705481486975324, -0.2794154981989387, -0.2310777882994052, -0.18216250427210898, -0.1327919088525308, -0.08308940281751057, -0.03317921654757102, 0}; //{sin(0), sin(0.05), sin(0.1) ...}
double cosLookup[] = {1, 0.9987502603949663, 0.9950041652780257, 0.9887710779360422, 0.9800665778412416, 0.9689124217106447, 0.955336489125606, 0.9393727128473789, 0.9210609940028851, 0.900447102352677, 0.8775825618903728, 0.8525245220595058, 0.8253356149096783, 0.7960837985490559, 0.7648421872844884, 0.7316888688738208, 0.6967067093471653, 0.6599831458849821, 0.6216099682706643, 0.5816830894638833, 0.5403023058681395, 0.49757104789172674, 0.4535961214255771, 0.40848744088415695, 0.3623577544766732, 0.31532236239526823, 0.26749882862458696, 0.21900668709304105, 0.16996714290024037, 0.12050276936736595, 0.07073720166770224, 0.02079482780309176, -0.02919952230128948, -0.07912088880673475, -0.12884449429552552, -0.17824605564949297, -0.22720209469308797, -0.2755902468245138, -0.3232895668635044, -0.37018083135128793, -0.4161468365471432, -0.46107269137671353, -0.5048461045998579, -0.5473576654802714, -0.5885011172553458, -0.6281736227227391, -0.666276021279824, -0.7027130767735537, -0.7373937155412451, -0.7702312540473069, -0.8011436155469331, -0.8300535352352216, -0.8568887533689465, -0.8815821958782852, -0.9040721420170604, -0.9243023786324629, -0.9422223406686575, -0.9577872375530897, -0.97095816514959, -0.9817022029984536, -0.9899924966004451, -0.995808324539061, -0.9991351502732794, -0.999964658471342, -0.9982947757947532, -0.9941296760805466, -0.9874797699088654, -0.9783616785819349, -0.9667981925794621, -0.952818214594306, -0.9364566872907979, -0.9177545059662777, -0.8967584163341491, -0.8735208976839403, -0.8481000317104109, -0.8205593573395638, -0.7909677119144201, -0.7593990591375116, -0.7259323042001442, -0.690651096560512, -0.6536436208636166, -0.6150023765255793, -0.5748239465332743, -0.5332087560371603, -0.4902608213407056, -0.44608748991379915, -0.40079917207998195, -0.3545090650481386, -0.30733286997842696, -0.2593885027896338, -0.21079579943078752, -0.1616762163536944, -0.11215252693506281, -0.06234851460700052, -0.01238866346289944, 0.03760215288796768, 0.08749898343943754, 0.1371771121008985, 0.18651236942256616, 0.2353814429544417, 0.2836621854632169, 0.3312339202367445, 0.3779777427129712, 0.4237768176794186, 0.4685166713003677, 0.5120854772418315, 0.5543743361791519, 0.5952775479885976, 0.6346928759426257, 0.6725218022484574, 0.7086697742912519, 0.7430464409664022, 0.7755658785102423, 0.8061468052647083, 0.8347127848391529, 0.8611924171615145, 0.8855195169413131, 0.907633279098408, 0.9274784307440309, 0.9450053693342231, 0.9601702866503623, 0.9729352782968943, 0.983268438442582, 0.9911439395684671, 0.9965420970232163, 0.999449418224499, 1}; // cos(0), cos(0.05), cos(0.1) ...

double mathmap(double x, double in_min, double in_max, double out_min, double out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
};

double dmod(double x, double y) {
    return x - (int)(x/y) * y;
};

double floor(double value, double precision = 1){
    if(dmod(value, precision) == 0){
        return value;
    };
    return value - dmod(value, precision);
};

double ceil(double value, double precision = 1){
    if(dmod(value, precision) == 0){
        return value;
    };
    return value + dmod(value, precision);
};

double round(double value, double precision = 1){
    if (value - floor(value, precision) < precision / 2) {
        return floor(value, precision);
    } else {
        return ceil(value, precision);
    };
};

double percentLerp(double a, double b, double percent){
    return a + (b - a) * percent;
};

double sin(double radians){
    if(radians > TWO_PI){
        radians = dmod(radians, TWO_PI);
    };
    double sinVal1 =  sinLookup[(int)floor(radians*20)];
    double sinVal2 =  sinLookup[(int)ceil(radians*20)];
    return (sinVal1+sinVal2)/2;
};


double cos(double radians){
    if(radians > TWO_PI){
        radians = dmod(radians, TWO_PI);
    };
    double cosVal1 =  cosLookup[(int)floor(radians*20)];
    double cosVal2 =  cosLookup[(int)ceil(radians*20)];
    return (cosVal1+cosVal2)/2;
};

double min(double a, double b){
    return (a<b)?a:b;
};
double max(double a, double b){
    return (a>b)?a:b;
};

double constrain(double val, double min_val, double max_val) {
  return min(max_val, max(min_val, val));
};

double constantlerp(double A, double B, double t) {
    return A + constrain((B - A), -1, 1) * t;
};

double abs(double x){
    if (x < 0) {
        return -x;
    } else {
        return x;
    };
};

double sqrt(double x, double epsilon = 0.00001) {
  if (x <= 0) {
    return 0;
  };

  double guess = 1.0;
  while (abs(guess*guess - x) >= epsilon) {
    guess = (guess + x / guess) / 2;
  };
  return guess;
};

double distance(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;
    double dy = y2 - y1;
    return sqrt(dx*dx + dy*dy);
};
