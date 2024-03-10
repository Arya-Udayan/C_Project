#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define PARKING_RATE 5.0 

struct parking_spot {
    int spot_number;
    bool is_occupied;
    int user_id;
    int vehicle_id;
    bool is_peak_hour;
    int vehicle_type;
    int parking_duration;
    float parking_fee;
    struct parking_spot* next; // Pointer to the next spot in the linked list
};

struct parking_spot* parking_lot = NULL; 

// Function to initialize the parking lot
void initialize_parking_lot(int max_spots) {
    for (int i = 1; i <= max_spots; i++) {
        struct parking_spot* spot = (struct parking_spot*)malloc(sizeof(struct parking_spot));
        spot->spot_number = i;
        spot->is_occupied = false;
        spot->next = parking_lot;
        parking_lot = spot;
    }
}

// Function to reserve a parking spot
void reserve_parking_spot(int spot_number, int vehicle_id, int new_user_id) {
    struct parking_spot* current = parking_lot;
    while (current != NULL) {
        if (current->spot_number == spot_number && !current->is_occupied) {
            current->is_occupied = true;
            current->user_id = new_user_id;
            current->vehicle_id = vehicle_id;
            printf("Please save your user ID %d for future use.\n", current->user_id);
            printf("Parking spot %d reserved successfully.\n", spot_number);
            return;
        }
        current = current->next;
    }
    printf("Parking spot %d is already occupied or does not exist.\n", spot_number);
}

// Function to vacate a parking spot
void free_parking_spot(int spot_number, int user_id) {
    struct parking_spot* current = parking_lot;
    while (current != NULL) {
        if (current->spot_number == spot_number && current->is_occupied) {
            if (current->user_id == user_id) {
                int parking_duration;
                printf("Enter the number of hours the spot was occupied: ");
                scanf("%d", &parking_duration);
                current->is_occupied = false;
                current->user_id = 0;
                current->vehicle_id = 0;
                current->parking_duration = parking_duration;
                current->parking_fee = PARKING_RATE * parking_duration;
                printf("Parking spot %d freed successfully.\n", spot_number);
                printf("Total parking fee: $%.2f\n", current->parking_fee);
                return;
            } else {
                printf("You are not authorized to vacate this spot.\n");
                return;
            }
        }
        current = current->next;
    }
    printf("Parking spot %d is already vacant or does not exist.\n", spot_number);
}

// Function to free memory and clean up the linked list
void cleanup_parking_lot() {
    struct parking_spot* current = parking_lot;
    while (current != NULL) {
        struct parking_spot* temp = current;
        current = current->next;
        free(temp);
    }
}

int main() {
    int max_spots = 50;
    initialize_parking_lot(max_spots);
    int user_count;
    int vacate_user_count;
    printf("How many users are there to reserve parking lots: \n");
    scanf("%d", &user_count);
    for (int i = 1; i <= user_count; i++) {
        printf("\nRegistration of user %d started ", i);
        int reservation_lots;
        int vehicle_id;
        printf("\nWhich lots to be reserved : ");
        scanf("%d", &reservation_lots);
        printf("Please enter your vehicle ID : ");
        scanf("%d", &vehicle_id);
        int new_user_id = rand() % 50 + 1;
 reserve_parking_spot( reservation_lots,vehicle_id,new_user_id);
}
printf("\nHow many users want to vacate the slots\n");
    scanf("%d", &vacate_user_count);
    for (int i = 1; i <= vacate_user_count; i++) {
        int user_id;
        int free_spots;
        printf("User %d can vacate the parking lot \n", i);
        printf("Free Lots : ");
        scanf("%d", &free_spots);
        printf("\nEnter the user ID : ");
        scanf("%d", &user_id);
        free_parking_spot(free_spots, user_id);
    }
    cleanup_parking_lot(); // Free memory before exiting
    return 0;
}

