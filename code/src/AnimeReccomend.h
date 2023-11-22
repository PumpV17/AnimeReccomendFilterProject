#pragma once 
#include <string>
#include <vector>
#include <iostream>

struct AnimeShow
{
    std::string title;
    double score;
    std::string binary_genre;
    double similarityScore;

    // Overloading the stream insertion operator (<<) for easy printing
    friend std::ostream& operator<<(std::ostream& os, const AnimeShow& anime)
    {
        os << "Title: " << anime.title << ", Score: " << anime.score
           << ", Genre: " << anime.binary_genre << ", Similarity Score: " << anime.similarityScore;
        return os;
    }

    // Overloading the equality operator (==)
    friend bool operator==(const AnimeShow& lhs, const AnimeShow& rhs)
    {
        return lhs.title == rhs.title &&
               lhs.score == rhs.score &&
               lhs.binary_genre == rhs.binary_genre &&
               lhs.similarityScore == rhs.similarityScore;
    }

    // Overloading the inequality operator (!=)
    friend bool operator!=(const AnimeShow& lhs, const AnimeShow& rhs)
    {
        return !(lhs == rhs);
    }


};

class AnimeReccomend
{
    public:
        std::vector<AnimeShow>findSimilarAnimes(std::vector<AnimeShow>& database, std::vector<AnimeShow>& favoriteAnimes, int k);
        double dotProduct(const std::vector<double> vec1, const std::vector<double> vec2);
        double magnitude(const std::vector<double>& vec);
        double cosineSimilarity(const AnimeShow show1, const AnimeShow show2);
        static bool compareSimScore(const AnimeShow& a, const AnimeShow& b);



    private:
        std::vector<AnimeShow> reccomendList;


};