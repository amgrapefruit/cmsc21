/**
 * Author: Aaron Michael M. Ariedo
 * Date: 19 August 2025
 * CMSC 21: Exercise 1
 */

#include <stdio.h>
#include <math.h>

int main() {
	int choice = 0;
	float weight = 0.0;
	float height = 0.0;
	float height_feet = 0.0;
	float height_inch = 0.0;
	float bmi = 0.0;

	while (choice != 3) // repeat while 3 (exit) is not selected
	{
		weight = 0.0;
		height = 0.0;
		height_feet = 0.0;
		height_inch = 0.0;
		bmi = 0.0;

		printf("=====Menu=====\n");
		printf("[1] Metric\n");
		printf("[2] Standard\n");
		printf("[3] Exit\n");
		printf("Please enter your choice: ");
		scanf("%d", &choice); // scan for choice

		if (choice == 1) { // metric
			printf("Enter weight in kilograms: ");
			scanf("%f", &weight);

			printf("Enter height in centimeters: ");
			scanf("%f", &height);

			bmi = weight / (height/100 * height/100);
			printf("Your BMI is: %.2f\n", roundf(bmi*100)/100);

		} else if (choice == 2) { // standard
			printf("Enter weight in pounds: ");
			scanf("%f", &weight);

			printf("Enter height in feet: ");
			scanf("%f", &height_feet);

			printf("Enter height in inches: ");
			scanf("%f", &height_inch);

			height = height_feet * 12 + height_inch; // convert the inputted feet into total height in inches
			bmi = weight / (height * height) * 703;
			printf("Your BMI is: %.2f\n", roundf(bmi*100)/100);

		}

		// print bmi category per bmi value
		if (bmi > 30) { // obese
			printf("You are obese.\nPlease go see a health professional.\n\n");
		}
		else if (bmi >= 25) { // overweight
			printf("You are overweight.\nPlease keep your health in check.\n\n");
		}
		else if (bmi >= 18.5) { // normal
			printf("You are normal weight.\nYou are likely doing a good job with your health. Good Job!\n\n");
		}
		else if (bmi > 0) { // underweight
			printf("You are underweight.\nPlease go see a health professional.\n\n");
		}
	}

	return 0;
}


