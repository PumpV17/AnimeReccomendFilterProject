#include "AnimeReccomend.h"
#include <cmath>
#include <algorithm>
#include <stdexcept>
#include <numeric>


const double epsilon = 1e-6;

std::vector<AnimeShow> AnimeReccomend::findSimilarAnimes(std::vector<AnimeShow>& database, std::vector<AnimeShow>& favoriteAnimes, int k)
{
    for (AnimeShow& data : database)
    {
        std::vector<AnimeShow> temp;
        std::vector<double> tempList;
        bool hasPerfectMatch = false;

        for (AnimeShow& show : favoriteAnimes)
        {
            double sim = cosineSimilarity(show, data);
            tempList.push_back(sim);

            if (std::abs(sim - 1.0) < epsilon) {
                hasPerfectMatch = true;
            }
        }

        if (!hasPerfectMatch) {
            double maxSimilarity = *std::max_element(tempList.begin(), tempList.end());
            data.similarityScore = maxSimilarity < 1.0 ? maxSimilarity : 0.0;
        }
        else {
            data.similarityScore = 0.0;  
        }
    }

    std::partial_sort(database.begin(), database.begin() + k, database.end(), compareSimScore);

    return {database.begin(), database.begin() + k};
}


double AnimeReccomend::dotProduct(const std::vector<double> vec1, const std::vector<double> vec2)
{
    double result = 0.0f;
    //if(vec1.size() != vec2.size())
    //{
        //throw std::invalid_argument("Input vectors must have the same size");
    //}
    

    for(size_t i = 0; i < vec1.size(); ++i)
    {
        result += vec1[i] * vec2[i];
    }

    return result;
}

double AnimeReccomend::magnitude(const std::vector<double>& vec)
{
    double result = 0.0f;
    for(double item : vec)
    {
        result += item * item;
    }

    return std::sqrt(result);
}

double AnimeReccomend::cosineSimilarity(const AnimeShow show1, const AnimeShow show2)
{
    double result = 0.0f;

    double normalizedScore1 = show1.score / 10.0;  
    double normalizedScore2 = show2.score / 10.0;

    std::vector<double> s1 = {normalizedScore1 * 0.005};
    std::vector<double> s2 = {normalizedScore2 * 0.005};

    std::vector<double>binary1, binary2;
    for(char c : show1.binary_genre)
    {
        binary1.push_back(static_cast<double>(c - '0') * 0.5);
    }

    for(char c : show2.binary_genre)
    {
        binary2.push_back(static_cast<double>(c - '0') * 0.5);
    }

    s1.insert(s1.end(), show1.binary_genre.begin(), show1.binary_genre.end());
    s2.insert(s2.end(), show2.binary_genre.begin(), show2.binary_genre.end());


    double dotResult = dotProduct(s1,s2);
    double mag1 = magnitude(s1);
    double mag2 = magnitude(s2);

    return (mag1 == 0 || mag2 == 0)? -1.0f : (dotResult)/(mag1 * mag2);
}


bool AnimeReccomend::compareSimScore(const AnimeShow& a, const AnimeShow& b)
{
    return (a.similarityScore > b.similarityScore);
}


