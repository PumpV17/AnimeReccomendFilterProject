#define CATCH_CONFIG_MAIN
#include "code/catch_amalgamated.hpp"
#include "AnimeReccomend.h"

TEST_CASE("Test AnimeReccomend class") {
    AnimeReccomend animeReccomend;

    SECTION("Test dotProduct function") {
        std::vector<double> vec1 = {1, 2, 3};
        std::vector<double> vec2 = {1, 2, 3};
        REQUIRE(animeReccomend.dotProduct(vec1, vec2) == 14.0f);
        REQUIRE(animeReccomend.dotProduct(vec1, vec1) == 14.0f); // Test with identical vectors
        REQUIRE(animeReccomend.dotProduct(vec2, vec2) == 14.0f); // Test with identical vectors
    }

    SECTION("Test magnitude function") {
        std::vector<double> vec = {1, 2, 2};
        REQUIRE(std::abs(animeReccomend.magnitude(vec) - 3) < 0.0001);
        REQUIRE(animeReccomend.magnitude(vec) == animeReccomend.magnitude(std::vector<double>{-1, -2, -2})); // Test negative values
    }

    SECTION("Test cosineSimilarity function") {
        AnimeShow show1 = {"Haikyuu!! Second Season", 8.82, "00000100000000000000000000100000000100000"}; // sample with Haikyuu!! Second Season
        AnimeShow show2 = {"Haikyuu!!: Karasuno Koukou vs. Shiratorizawa Gakuen Koukou", 8.94, "00000100000000000000000000100000000100000"}; // sample with Haikyuu!!: Karasuno Koukou vs. Shiratorizawa Gakuen Koukou

        SECTION("Similar shows") {
            REQUIRE(animeReccomend.cosineSimilarity(show1, show2) > 0.95);
        }

        SECTION("Identical shows") {
            REQUIRE(animeReccomend.cosineSimilarity(show1, show1) == 1);
            REQUIRE(animeReccomend.cosineSimilarity(show2, show2) == 1);
        }
    }

    SECTION("Test findSimilarAnimes function") {
        std::vector<AnimeShow> database = {
            {"Haikyuu!! Second Season", 8.82, "00000100000000000000000000100000000100000"},
            {"Haikyuu!!: Karasuno Koukou vs. Shiratorizawa Gakuen Koukou", 8.94, "00000100000000000000000000100000000100000"},
            {"Fullmetal Alchemist: Brotherhood", 9.23, "10100101000000010010000000000000000000000"},
            {"Mob Psycho 100 II", 8.89, "00100000000000000000000000000000010000000"},
            {"Kimetsu no Yaiba", 8.92, "00001000000100000000000000000000100000000"}
        };
        std::vector<AnimeShow> favoriteAnimes = {
            {"Fullmetal Alchemist: Brotherhood", 9.23, "10100101000000010010000000000000000000000"}
        };

        std::vector<AnimeShow> recommended = animeReccomend.findSimilarAnimes(database, favoriteAnimes, 5);

        SECTION("Check number of recommendations") {
            REQUIRE(recommended.size() == 5);
        }

        SECTION("Uniqueness in recommendations") {
            std::vector<std::string> titles;
            for (const auto& show : recommended) {
                titles.push_back(show.title);
            }
            for (size_t i = 0; i < titles.size(); ++i) {
                for (size_t j = i + 1; j < titles.size(); ++j) {
                    REQUIRE(titles[i] != titles[j]);
                }
            }
        }
    }

    SECTION("Test compareSimScore function") {
        AnimeShow show1 = {"Show1", 8.0, "00001"};
        AnimeShow show2 = {"Show2", 9.0, "10000"};

        SECTION("Compare shows by similarity score") {
            REQUIRE(animeReccomend.compareSimScore(show1, show2));
        }

        SECTION("Compare shows by similarity score (opposite order)") {
            REQUIRE_FALSE(animeReccomend.compareSimScore(show2, show1));
        }
    }
}
