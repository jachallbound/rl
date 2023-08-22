/* Macros */
#define STR_LEN 128
#define MAX_CARS 20
#define MAX_CARS_MOVE 5
#define MV 2 /* cost to move car */
#define R1 10 /* Return when a car is available to rent */
#define R0 0 /* Return when no car is available to rent */
#define RQ1 3 /* Expected rent requests at lot 1 */
#define RQ2 4 /* Expected rent requests at lot 2 */
#define RT1 3 /* Expected car returns at lot 1 */
#define RT2 2 /* Expected car returns at lot 2 */
#define G 0.9 /* gamma, discounted returns */
#define POISSON_BOUND 10 /* upper bound of poisson probability */
