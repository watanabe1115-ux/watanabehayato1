#include <stdio.h>

int factorial(int target) {
if (target <= 1) {
return target;
}
else {
return target * factorial(target - 1);
}
}