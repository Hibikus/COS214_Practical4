#include "FilmingState.h"
#include "Shot.h"
#include "InReviewState.h"
#include <iostream>

FilmingState::~FilmingState()
{
}

std::string FilmingState::getName()
{
    return "Filming";
}

void FilmingState::schedule(Shot* s)
{
    (void)s;
    std::cout << "Cannot schedule a shot that is already being filmed." << std::endl;
}

void FilmingState::startFilming(Shot* s)
{
    (void)s;
    std::cout << "The shot is already being filmed." << std::endl;
}

void FilmingState::submitForReview(Shot* s)
{
    static InReviewState inReviewState;
    s->setState(&inReviewState);
}

void FilmingState::approve(Shot* s)
{
    (void)s;
    std::cout << "Cannot approve a shot while it is being filmed." << std::endl;
}

void FilmingState::requestReshoot(Shot* s)
{
    (void)s;
    std::cout << "Cannot request a reshoot while the shot is being filmed." << std::endl;
}