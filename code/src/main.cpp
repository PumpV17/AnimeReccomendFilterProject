#include "AnimeReccomend.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

int main() {
    // Create instances of AnimeReccomend and vectors to store anime data
    AnimeReccomend animeReccomend;
    std::vector<AnimeShow> database;
    std::vector<AnimeShow> favoriteAnimes;

    // Read the CSV file
    std::ifstream file("C:/Users/Pump/AnimeReccomendFilterProject/code/src/csv/anime_dataset_full.csv");
    if (!file.is_open()) {
        std::cerr << "Error opening file.\n";
        return 1;
    }

    // Read and parse the CSV file
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string title, score, binary_genre;

        // Use getline to split the line into comma-separated values
        if (std::getline(iss, title, ',') && std::getline(iss, score, ',') && std::getline(iss, binary_genre)) {
            //std::cout << "Read values: Title = " << title << ", Score = " << score << ", Binary Genre = " << binary_genre << std::endl;

            try {
                double scoreValue = std::stod(score);
                AnimeShow anime = {title, scoreValue, binary_genre};
                database.push_back(anime);
            } catch (const std::invalid_argument& e) {
                //std::cerr << "Error converting score to double: " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error parsing line: " << line << std::endl;
        }
    }

    // Assume multiple favorite animes
    //favoriteAnimes.push_back({"Oshi No Ko", 8.74, "00000000100000000000000000000000100000000"});
    favoriteAnimes.push_back({"One Piece",8.71,"10100101000000000000000000000000000010000"});
    favoriteAnimes.push_back({"Naruto",7.93,"10100000000000001000000000000000000010000"});
    favoriteAnimes.push_back({"Boku no Hero Academia 2nd Season",8.6,"00100000000000000000000000100000000010000"});
    favoriteAnimes.push_back({"Code Geass: Hangyaku no Lelouch",8.76,"00000100000000000110000000010000000010000"});

    // Find similar animes
    int k = 100;
    std::vector<AnimeShow> recommendations = animeReccomend.findSimilarAnimes(database, favoriteAnimes, k);

    // Display recommendations
    std::cout << "Top " << k << " Recommended Animes:\n";
    for (const auto& recommendation : recommendations) {
        if(recommendation.score != 0 && recommendation.similarityScore != 0)
        std::cout << "Title: " << recommendation.title << ", Score: " << recommendation.score << ", Similarity: " << (recommendation.similarityScore - 0.9999)*1000000 <<"%\n";
    }

    return 0;
}
