/**
 * @file input.h
 * @author ESTG
 * @date 28-10-2023
 * @version 1
 *
 * @copyright Copyright (C) ESTG 2023. All Rights MIT Licensed.
 *
 * @brief A header file providing utility functions for user input validation and retrieval.
 *
 * This header file contains a collection of functions designed to facilitate user input
 * in a C or C++ program. It includes functions for obtaining integers, floats, doubles,
 * characters, and strings from the user while performing input validation to ensure
 * that the entered values are within specified ranges or constraints.
 * 
 */

#ifndef INPUT_H
#define INPUT_H

/**
 * @brief This function prompts the user to input an integer within a specified range and displays a custom message.
 * @param minValor The minimum valid integer value.
 * @param maxValor The maximum valid integer value.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided integer value within the specified range.
 */
int getInt(int minValor, int maxValor, char *msg);

/**
 * @brief This function prompts the user to input a floating-point number within a specified range and displays a custom message.
 * @param minValor The minimum valid floating-point value.
 * @param maxValor The maximum valid floating-point value.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided floating-point value within the specified range.
 */
float getFloat(float minValor, float maxValor, char *msg);

/**
 * @brief This function prompts the user to input a double-precision floating-point number within a specified range and displays a custom message.
 * @param minValor The minimum valid double value.
 * @param maxValor The maximum valid double value.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided double-precision floating-point value within the specified range.
 */
double getDouble(double minValor, double maxValor, char *msg);

/**
 * @brief This function prompts the user to input a single character and displays a custom message.
 * @param msg A custom message to prompt the user for input.
 * @return The user-provided character.
 */
char getChar(char *msg);

/**
 * @brief This function reads a string of characters from the user with a specified maximum length and displays a custom message.
 * @param string A character array to store the user-provided string.
 * @param tamanho The maximum number of characters that can be read (including null terminator).
 * @param msg A custom message to prompt the user for input.
 * @return This function does not return a value. It populates the string parameter with the user's input.
 */
void readString(char *string, unsigned int tamanho, char *msg);

#endif /* INPUT_H */


