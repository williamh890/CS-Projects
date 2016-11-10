#include ".../Headers/boolChecks"

cout << "Made it";

bool legalPosition(vector<vector<entity>> bounds, int xPos, int yPos)
{
    return (bounds[yPos][xPos] != wall);
}
