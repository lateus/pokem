#include "md1database.h"

/* Difficulties */
/*
    The array bellow contains as many elements as dungeons, and each element contains as many elements as floors
    have the corresponding dungeon plus 1, because the first element count the number of floors of the respective dungeon.
    An element value (except the first) correspond to a difficulty-referencial value (depends of the dungeon and floor).
    Also, the number of floors and the name of the corresponding dungeon are commented for each one.
*/
 const int difficulties[][100] = {
    {  3,  1,1,1 }, /* 3 - Tiny Woods */
    {  5,  1,1,1,1,1 }, /* 5 - Thunderwave Cave */
    {  9,  1,1,1,1,1,1,1,1,1 }, /* 9 - Mt. Steel */
    { 13,  2,2,2,2,2,2,2,2,2,2,2,2,2 }, /* 13 - Sinister Woods */
    {  9,  2,2,2,2,2,2,2,3,3 }, /* 9 - Silent Chasm */
    { 10,  3,3,3,3,3,3,3,3,3,3 },   /* 10 - Mt. Thunder */
    {  3,  3,3,3 }, /* 3 - Mt. Thunder Peak */
    { 12,  4,4,4,4,4,4,4,4,4,4,4,4 },   /* 12 - Great Canyon */
    { 14,  4,4,4,4,4,4,4,4,4,4,4,4,4,4 },   /* 14 - Lapis Cave */
    { 12,  4,4,4,4,4,4,4,4,4,4,4,4 },   /* 12 - Mt. Blaze */
    {  3,  4,4,4 }, /* 3 - Mt. Blaze Peak */
    {  9,  4,4,4,4,4,5,5,5,5 }, /* 9 - Frosty Forest */
    {  5,  5,5,5,5,5 }, /* 5 - Frosty Grotto */
    { 15,  5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 }, /* 15 - Mt. Freeze */
    {  4,  5,5,5,5 }, /* 4 - Mt. Freeze Peak */
    { 23,  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 }, /* 23 - Magma Cavern */
    {  3,  6,6,6 }, /* 3 - Magma Cavern Pit */
    { 25,  6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6 }, /* 25 - Sky Tower */
    {  9,  7,7,7,7,7,7,7,7,7 }, /* 9 - Sky Tower Summit */
    { 40,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9 }, /* 40 - Stormy Sea */
    { 99,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11 }, /* 99 - Silver Trench */
    { 20,  7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8 }, /* 20 - Meteor Cave */
    {  4,  5,5,5,5 }, /* 4 - Mt. Freeze Peak */
    { 99,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12 }, /* 99 - Western Cave */
    {  0  }, /* [INVALID] */
    {  0  }, /* [INVALID] */
    { 99,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12 }, /* 99 - Whish Cave */
    { 99,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12 }, /* 99 - Buried Relic */
    { 11,  1,1,1,1,1,1,1,1,1,1,1 }, /* 11 Pitfall Valley */
    { 25,  7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9 }, /* 25 - Northern Range */
    {  0  }, /* [INVALID] */
    { 20,  7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8 },   /* 20 - Desert Region */
    { 50,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9 }, /* 50 - Southern Cavern */
    { 30,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9 }, /* 30 - Wyvern Hill */
    { 30,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9 }, /* 30 - Fiery Field */
    { 30,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9 }, /* 30 - Northwind Field */
    { 20,  7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8 }, /* 20- Solar Cave */
    { 30,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9 }, /* 30 - Lightning Field */
    { 15,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 }, /* 15 - Darknight Relic */
    {  0  }, /* [INVALID] */
    { 19,  7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8 }, /* 19 - Murky Cave */
    { 30,  7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8 }, /* 30 - Grand Sea */
    { 10,  5,5,5,5,5,5,5,5,5,5 }, /* 10 - Uproar Forest */
    { 15,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 }, /* 15 - Oddity Cave */
    { 20,  7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,8 }, /* 20 - Remains Islands */
    { 20,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8 }, /* 20 - Marvelous Sea */
    { 30,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9 }, /* 30 - Fantasy Strait */
    {  4,  1,1,1,1 }, /* 4 - Rock Path */
    {  4,  1,1,1,1 }, /* 4 - Snow Path */
    {  0  }, /* [INVALID] */
    {  0  }, /* [INVALID] */
    {  0  }, /* [INVALID] */
    { 69,  1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 }, /* 69 - Dojo Registration */
    { 15,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 }, /* 15 - Howling Forest */
    {  0  }, /* [INVALID] */
    { 30,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9 }, /* 30 - Fantasy Strait */
    { 19,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7 }, /* 19 - Waterfall Pound */
    { 11,  7,7,7,7,7,7,7,7,7,7,7 }, /* 11 - Unown Relic */
    { 99,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12 }, /* 99 - Joyous Tower */
    { 75,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12 }, /* 75 - Far-off Sea */
    { 40,  7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,10,10,10,10,10 }, /* 40 - Mt. Faraway */
    {  0  }, /* [INVALID] */
    { 99,  8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14 } /* 99 - Purity Forest */
};


/* Difficulties characters */
const int difficultiesCharsCount = 7;
const char* difficultiesChars = "EDCBAS*";


/* Dungeon-up or dungeon-down (negative floors are `B#F`, positive floors are ` #F`, '\?' are for INVALID dungeons) */
    /* PD: I use the scape secuence '\?' instead of just '?' because of trigraphs */
const char* dungeonUpOrDown = "BB  B   B      BB  BBB B\?\?BBB \? B   B B\?BBBBBBBBB\?\?\?B \?BBB B \? ";


/* Items in dungeons */
/* the first element of each sub-array represents his size */
const int itemsInDungeons[][145] = {
    {   3,  55,66,105 }, /* Tiny Woods */
    {   8,  7,55,66,67,69,72,82,105 }, /* Thunderwave Cave */
    {  15,  7,55,66,67,72,77,86,92,105,182,183,184,189,200,218 }, /* Mt. Steel */
    {  28,  55,58,63,66,67,72,77,82,86,88,89,90,91,92,93,94,95,96,97,105,182,183,184,188,200,201,202,218 }, /* Sinister Woods */
    {  28,  7,19,33,55,63,66,67,72,77,82,86,87,88,90,92,94,96,98,99,100,105,182,183,184,200,201,202,218 }, /* Silent Chasm */
    {  44,  7,19,25,33,55,66,67,72,77,82,86,87,88,90,91,92,93,94,95,96,98,101,105,129,130,133,134,136,143,144,145,151,152,154,155,158,164,165,166,167,168,169,170,232 }, /* Mt. Thunder */
    {  15,  55,72,77,86,87,89,90,91,92,93,94,95,98,102,105 }, /* Mt. Thunder Peak */
    {  43,  7,19,33,55,63,66,67,72,77,82,86,87,90,91,92,93,94,95,96,98,102,105,129,130,133,134,136,143,144,145,151,152,154,155,158,164,165,166,167,168,169,170,232 }, /* Great Canyon */
    {  45,  7,19,20,25,31,55,66,67,72,77,82,86,87,88,90,91,92,93,94,95,96,98,102,105,129,130,133,134,136,143,144,145,151,152,154,155,158,164,165,166,167,168,169,170,232 }, /* Lapis Cave */
    {  32,  7,19,33,87,92,93,94,98,101,102,105,129,130,133,134,136,143,144,145,151,152,154,155,158,164,165,166,167,168,169,170,232 }, /* Mt. Blaze */
    {   2,  87,105 }, /* Mt. Blaze Peak */
    {  44,  7,19,20,31,33,55,66,67,72,77,82,86,88,90,91,92,93,94,95,96,101,102,105,129,130,133,134,136,143,144,145,151,152,154,155,158,164,165,166,167,168,169,170,232 }, /* Frosty Forest */
    {   7,  55,58,67,77,88,91,105 }, /* Frosty Grotto */
    {  53,  2,7,10,19,20,21,31,33,55,58,66,67,72,77,82,86,88,90,91,92,93,94,95,96,98,99,100,101,102,105,129,130,133,134,136,137,143,144,145,148,151,152,154,155,158,164,165,166,167,168,169,170,232 }, /* Mt. Freeze */
    {  16,  55,58,67,77,86,88,90,91,92,93,94,95,96,98,102,105 }, /* Mt. Freeze Peak */
    {  48,  2,3,7,10,12,17,18,19,20,21,22,25,29,31,33,82,87,98,101,102,105,125,129,130,133,134,136,143,144,145,146,148,150,151,152,154,155,158,159,162,164,165,166,167,168,169,170,232 }, /* Magma Cavern */
    {   1,  105 }, /* Magma Cavern Pit */
    {  54,  2,3,10,12,17,18,19,20,21,22,25,29,31,33,35,82,91,93,95,98,99,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,157,158,159,162,164,165,166,167,168,169,170,232 }, /* Sky Tower */
    {  45,  10,12,16,17,18,19,20,21,22,29,31,33,35,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,157,158,159,162,164,165,166,167,168,169,170 }, /* Sky Tower Summit */
    {  89,  7,10,11,12,13,17,18,19,20,21,22,25,30,31,35,44,53,55,61,65,66,67,68,69,71,72,77,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Stormy Sea */
    {  74,  2,3,7,10,11,12,13,17,18,19,20,21,22,25,30,31,35,44,53,55,63,66,67,68,69,71,77,84,88,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Silver Trench */
    {   1,  105 }, /* Meteor Cave */
    {  16,  55,58,67,77,86,88,90,91,92,93,94,95,96,98,102,105 }, /* Mt. Freeze Peak */
    {  16,  53,55,58,63,66,67,68,69,72,77,78,79,80,81,105,123 }, /* Western Cave */
    {  32,  1,2,3,7,9,53,55,56,61,65,67,68,71,72,77,82,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    {  32,  1,2,3,7,9,53,55,56,61,65,67,68,71,72,77,82,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    { 120,  1,2,3,7,9,10,11,12,13,15,17,18,19,20,21,22,24,27,29,30,31,33,34,35,38,42,43,44,45,53,55,56,57,58,61,63,64,65,66,67,68,69,71,72,75,76,77,85,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,163,164,165,166,167,168,169,170,173,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,195,196,197,199,200,201,202,203,204,207,208,211,212,213,214,218,219,221,222,223,232 }, /* Wish Cave */
    { 119,  1,2,3,7,9,10,11,12,13,14,15,17,18,19,20,21,22,24,27,29,30,31,33,34,35,38,42,44,45,53,55,56,57,58,61,63,64,65,66,67,68,69,71,72,75,76,77,82,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,163,164,165,166,167,168,169,170,173,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,195,196,197,199,200,201,202,203,204,207,208,211,212,214,218,219,221,222,223,232 }, /* Buried Relic */
    {  74,  2,3,7,10,12,16,17,18,19,20,21,22,25,29,30,31,53,55,58,63,64,65,66,67,72,77,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218,232 }, /* Pitfall Valley */
    {  74,  2,3,7,10,12,16,17,18,19,20,21,22,25,29,30,31,53,55,58,63,64,65,66,67,72,77,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218,232 }, /* Northern Range */
    { 104,  1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,53,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    {  55,  7,10,19,20,21,25,31,105,123,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Desert Region */
    {  65,  7,14,15,16,17,24,27,29,30,33,34,38,53,55,66,67,83,105,115,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Southern Cavern */
    {  84,  1,2,3,7,14,15,16,17,24,27,29,30,33,34,38,44,53,55,57,58,59,61,63,64,65,66,67,68,69,71,72,75,76,77,83,105,117,125,126,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Wyvern Hill */
    {  86,  1,2,3,7,14,15,16,17,24,27,29,30,33,34,38,53,55,57,58,59,61,63,64,65,66,67,68,69,71,72,75,76,77,78,79,80,81,82,105,113,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Fiery Field */
    {  86,  1,2,3,7,14,15,16,17,24,27,29,30,33,34,38,53,55,57,58,59,61,63,64,65,66,67,68,69,71,72,75,76,77,78,79,80,81,82,105,114,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Northwind Field */
    {  72,  1,7,10,11,12,13,17,18,30,31,34,35,44,45,53,55,64,66,67,72,77,105,111,112,123,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218,232 }, /* Solar Cave */
    {  86,  1,2,3,7,14,15,16,17,24,27,29,30,33,34,38,53,55,57,58,59,61,63,64,65,66,67,68,69,71,72,75,76,77,78,79,80,81,82,105,108,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Lightning Field */
    {  77,  1,2,3,7,8,10,11,12,13,14,15,16,17,18,19,20,21,22,24,27,29,30,31,32,33,34,35,38,39,40,41,42,44,45,53,55,58,63,66,67,68,69,72,77,84,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,157,158,159,162,164,165,166,167,168,169,170 }, /* Darknight Relic */
    { 105,  1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,53,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    {   1,  105 }, /* Murky Cave */
    {  73,  7,8,10,12,13,16,17,19,20,21,22,24,25,27,29,31,32,35,38,39,40,53,59,61,67,68,69,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,213,218 }, /* Grand Sea */
    {  10,  53,55,66,67,72,82,89,97,104,105 }, /* Uproar Forest */
    {  39,  7,19,30,33,34,53,55,63,66,67,72,77,82,86,87,88,90,92,94,96,98,99,100,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Oddity Cave */ 
    {  39,  7,19,30,33,34,53,55,63,66,67,72,77,82,86,87,88,90,92,94,96,98,99,100,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Remains Islands */
    {  44,  7,8,10,12,13,16,17,19,20,21,22,23,24,25,27,29,31,32,35,38,39,40,53,59,61,67,68,69,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Marvelous Sea */
    {  43,  7,8,10,12,13,16,17,19,20,21,22,23,24,25,27,29,31,32,35,38,39,40,53,59,61,67,68,69,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Fantasy Strait */
    {  25,  7,53,55,64,66,67,72,77,83,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Rock Path */
    {  25,  7,53,55,64,66,67,72,77,82,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Snow Path */
    {  42,  2,3,7,10,12,16,17,18,19,20,21,22,25,29,30,31,53,55,58,63,64,65,66,67,72,77,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    { 105,  1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,53,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    {  81,  1,2,3,7,10,12,13,16,17,19,20,21,22,23,24,25,27,29,31,32,35,38,39,40,53,55,56,58,59,61,63,64,65,66,67,68,69,71,72,75,76,77,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    {  26,  53,55,58,66,67,71,72,77,82,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102 }, /* Dojo Registration */
    {  68,  53,55,58,59,61,63,66,67,68,72,75,76,82,89,90,92,94,97,105,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,162,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218,232 }, /* Howling Forest */
    { 105,  1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,53,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    { 104,  1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,53,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Fantasy Strait */
    {   9,  8,53,55,66,67,71,72,77,105 }, /* Waterfall Pond */
    {  25,  7,8,53,55,65,66,67,71,77,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Unown Relic */
    { 125,  1,2,3,7,8,10,14,15,16,17,18,19,20,21,22,27,31,33,34,35,39,40,41,43,44,53,55,56,58,59,61,63,64,65,66,67,68,69,71,72,74,77,78,79,80,81,83,85,105,125,128,129,130,131,133,134,135,136,137,140,142,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,161,162,163,164,165,166,167,168,169,170,178,180,181,182,183,184,185,186,187,188,189,190,191,192,195,196,197,199,200,201,202,203,204,205,206,207,208,211,212,213,214,215,217,218,219,221,222,223,232 }, /* Joyous Tower */
    {  76,  7,8,10,12,13,16,17,19,20,21,22,23,24,25,27,29,31,32,35,38,39,40,53,59,61,67,68,69,105,109,110,123,125,128,129,130,133,134,136,137,140,143,144,145,146,148,150,151,152,153,154,155,156,157,158,164,165,166,167,168,169,170,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* Far-off Sea */
    {   8,  59,61,64,67,68,69,72,105 }, /* Mt. Faraway */
    { 105,  1,2,3,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,44,45,46,53,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,156,180,182,183,184,189,191,192,193,200,201,202,204,205,218 }, /* [INVALID] */
    { 144,  1,2,3,7,8,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,27,29,30,31,32,33,34,35,37,38,39,40,41,42,43,44,45,53,55,56,57,59,60,61,62,63,64,65,66,67,68,69,71,72,73,74,75,76,77,82,83,84,105,125,128,129,130,131,133,134,135,136,137,140,142,143,144,145,146,148,150,151,152,153,154,155,156,157,158,159,161,162,163,164,165,166,167,168,169,170,173,178,179,180,181,182,183,184,185,186,187,188,189,190,191,192,193,195,196,197,198,199,200,201,202,203,204,205,206,207,208,211,212,213,214,215,217,218,219,221,222,223,232 } /* Purity Forest */
};


/* Forbidden floors in dungeons */
/* the first element of each sub-array represents his size */
const int forbiddenFloorsInDungeons[][3] = {
    { 0 }, /* 0 - Tiny Woods */
    { 0 }, /* Thunderwave Cave */
    { 1,  9 }, /* Mt. Steel */
    { 1, 13 }, /* Sinister Woods */
    { 0 }, /* Silent Chasm */
    { 0 }, /* Mt. Thunder */
    { 1,  3 }, /* Mt. Thunder Peak */
    { 0 }, /* Great Canyon */
    { 0 }, /* Lapis Cave */
    { 0 }, /* Mt. Blaze */
    { 1,  3 }, /* 10 - Mt. Blaze Peak */
    { 0 }, /* Frosty Forest */
    { 0 }, /* Frosty Grotto */
    { 0 }, /* Mt. Freeze */
    { 0 }, /* Mt. Freeze Peak */
    { 0 }, /* Magma Cavern */
    { 2,  2,  3 }, /* Magma Cavern Pit */
    { 0 }, /* Sky Tower */
    { 1,  9 }, /* Sky Tower Summit */
    { 1, 40 }, /* Stormy Sea */
    { 1, 99 }, /* 20 - Silver Trench */
    { 1, 20 }, /* Meteor Cave */
    { 0 }, /* Mt. Freeze Peak */
    { 1, 99 }, /* Western Cave */
    { 0 }, /* [INVALID] */
    { 0 }, /* [INVALID] */
    { 2, 20, 99 }, /* Wish Cave */
    { 0 }, /* Buried Relic */
    { 0 }, /* Pitfall Valley */
    { 1, 25 }, /* Northern Range */
    { 0 }, /* 30 - [INVALID] */
    { 0 }, /* Desert Region */
    { 0 }, /* Southern Cavern */
    { 0 }, /* Wyvern Hill */
    { 1, 30 }, /* Fiery Field */
    { 1, 30 }, /* Northwind Field */
    { 0 }, /* Solar Cave */
    { 1, 30 }, /* Lightning Field */
    { 0 }, /* Darknight Relic */
    { 0 }, /* [INVALID] */
    { 0 }, /* 40 - Murky Cave */
    { 0 }, /* Grand Sea */
    { 1, 10 }, /* Uproar Forest */
    { 0 }, /* Oddity Cave */ 
    { 0 }, /* Remains Islands */
    { 0 }, /* Marvelous Sea */
    { 0 }, /* Fantasy Strait */
    { 0 }, /* Rock Path */
    { 0 }, /* Snow Path */
    { 0 }, /* [INVALID] */
    { 0 }, /* 50 - [INVALID] */
    { 0 }, /* [INVALID] */
    { 0 }, /* Dojo Registration */
    { 0 }, /* Howling Forest */
    { 0 }, /* [INVALID] */
    { 0 }, /* Fantasy Strait */
    { 0 }, /* Waterfall Pond */
    { 0 }, /* Unown Relic */
    { 0 }, /* Joyous Tower */
    { 0 }, /* Far-off Sea */
    { 1, 40 }, /* 60 - Mt. Faraway */
    { 0 }, /* [INVALID] */
    { 1, 99 }  /* Purity Forest */
};

/*
    Evolution checking - The first element is the size

    Truly speaking, the game does not have any restriction over
    any pkmn/item combination that can be used to generate a mail
    with a special flavor text about evolution or feed. However,
    we apply limitations for abvious reasons: we do not want a
    Charizard evolving with a Gravelerock, or a Pikachu eating an
    Insomniscope.
    We want as much consistence as the real game has, but we will
    also add the rest of evolution-related items.
*/
const int thunderStonePkmn[] = { 2, 25, 133 }; /* Pikachu and Eevee */
const int fireStonePkmn[]    = { 3, 37, 58, 133 }; /* Vulpix, Growlithe and Eevee */
const int waterStonePkmn[]   = { 5, 61, 90, 120, 133, 296 }; /* Poliwhirl, Shellder, Staryu, Eevee and Lombre */
const int leafStonePkmn[]    = { 4, 44, 70, 102, 299 }; /* Gloom, Weepinbell, Exeggcute and Nuzleaf */
const int sunStonePkmn[]     = { 2, 44, 191 }; /* Gloom and Sunkern */
const int moonStonePkmn[]    = { 5, 30, 33, 35, 39, 325 }; /* Nidorina, Nidorino, Clefairy, Jigglypuff and Skitty */
const int linkCablePkmn[]    = { 4, 64, 67, 75, 93 }; /* Kadabra, Machoke, Graveler and Haunter */
const int deepSeaScalePkmn[] = { 1, 394 }; /* Clamperl */
const int deepSeaToothPkmn[] = { 1, 394 }; /* Same as `deepSeaScalePkmn`: Clamperl */
const int dragonScalePkmn[]  = { 1, 117 }; /* Seadra */
const int kingsRockPkmn[]    = { 1, 80 }; /* Slowbro */
const int metalCoatPkmn[]    = { 2, 95, 123 }; /* Onix and Scyther */
const int upgradePkmn[]      = { 1, 137 }; /* Porygon */
const int sunRibbonPkmn[]    = { 1, 133 }; /* Eevee */
const int lunarRibbonPkmn[]  = { 1, 133 }; /* Same as `sunRibbonPkmn`: Eevee */
const int beautyScarfPkmn[]  = { 1, 374 }; /* Feebas */


/* Mission type */
const unsigned int missionTypeObjectiveCount = 6; /* The size of the array */
const char* missionTypeObjectiveStr[] = {
    "Help me!",
    "Find %s.",
    "Escort to %s.",
    "Find %s.",
    "Deliver %s.",
    "Friend rescue."
};


/** *** Standard titles and bodies *** **/

/** Titles (heads) first... */

const char* msgTitleStandard_HelpMe[] = {    /* Help me */
    "Help!",
    "I can't get out!",
    "I'm in trouble...",
    "I'm scared!",
    "I can't seem to get out.",
    "I'm lost.",
    "I was attacked!",
    "I fainted...",
    "I'm not a fighter",
    "I'm too tired to move.",
    "I was KO'd...",
    "Where am I?",
    "I'm sad and lonely.",
    "I can't get home!",
    "Help me!"
};

const char* msgTitleStandard_FindSomeone[] = {   /* Find Someone */
    "Please help %s!",
    "%s needs help!",
    "Hurry, save %s!",
    "Failed to return.",
    "Help!",
    "Somebody!",
    "I'm worried.",
    "Hasn't come back.",
    "Hurry!",
    "Disappearance!"
};

const char* msgTitleStandard_Escort[] = {    /* Escort */
    "Take me!",
    "I want to see %s.",
    "Please take me with you!",
    "Escort me!"
};

const char* msgTitleStandard_FindItem = "One %s wanted!";

const char* msgTitleStandard_DeliverItem = "Deliver one %s";


/** Now, bodies... */

const char* msgBodyStandard_1Of2_Help[] = {
    "I don't know how I did it, but I can't exit!",
    "I was attacked when I was sitting still!",
    "I'm simply no good at fighting.",
    "I got lost in this dungeon!",
    "This dungeon is scary!",
    "Fighting the tough foe was a mistake...",
    "I've reached my limit...",
    "I'm close to fainting...",
    "I lost in a battle...",
    "I was done in...",
    "Whoa! It's too rough here...",
    "I can't move another step.",
    "I'm famished..."
};

const char* msgBodyStandard_2Of2_Help[] = {
    "Please, I need help!",
    "Someone!",
    "Someone, help!",
    "I feel faint... Please help...",
    "Why? Why is everyone attacking me?",
    "Where am I? Help!",
    "Wroooooaaar! Someone!",
    "My consciousness is slipping... Help...",
    "Rescue is requested!",
    "Someone, please help!",
    "Help!",
    "...Gasp! Waaaaaaaah!",
    "Aiyeeeeeeeeh!"
};

const char* msgBodyStandard_1Of2_FindSomeone[] = {
    "%s passed out from the heat!",
    "%s may be endangered!",
    "%s is still missing.",
    "%s hasn't been heard from!",
    "%s can't swim!",
    "%s hasn't come back!",
    "%s might be unable to return.",
    "%s may be facing danger!",
    "%s appears to be injured!",
    "%s went missing this morning!",
    "%s is too scared to move!",
    "%s may be confused!",
    "%s appears to be freezing!",
    "Trouble may have found %s!",
    "%s was paralyzed!",
    "%s's whereabouts are unknown!",
    "I'm worried about %s!",
    "%s has been cornered!",
    "%s's been gone a long time!",
    "%s is about to faint!",
    "%s may have fainted already!",
    "It appears as if %s can't escape!",
    "%s was attacked by assailants!",
    "%s hasn't reemerged!",
    "%s appears to be helpless!",
    "%s is stuck in a cave!",
    "%s appears to be trapped!",
    "Something happened to %s!",
    "%s was attacked, maybe!",
    "%s is running out of time!",
    "I got separated from %s.",
    "Hurry, bring back %s.",
    "%s is too hungry to move!",
    "%s is fighting all alone!",
    "I'm worried for %s's safety!",
    "%s may have had an accident!",
    "%s appears to be lost!",
    "%s appears to be stuck!",
    "%s is lost!",
    "%s went the wrong way!",
    "%s's been missing three days!",
    "%s can't walk anymore!",
    "I can't contact %s!",
    "I lost contact with %s!",
    "%s fell into a trap!"
};

const char* msgBodyStandard_2Of2_FindSomeone[] = {
    "Please! Someone help!",
    "Please! I need help!",
    "Someone! Anyone?",
    "I don't care who it is! Please help!",
    "Help me!",
    "I'm pleading for help!",
    "Someone, help!",
    "Please send a rescue team!",
    "A rescue is urgently needed!",
    "Reward upon rescue!"
};

const char* msgBodyStandard_1Of2_Escort[] = {
    "%s is waiting for me!",
    "We promised to meet in the dungeon!",
    "I want to meet with %s.",
    "I'm worried about %s...",
    "I can't go by myself...",
    "I can't go on my own power...",
    "I'm too weak. It's not possible.",
    "%s is waiting in the dungeon.",
    "%s has been waiting forever...",
    "Hurry, %s is in trouble...",
    "I want to help %s!",
    "%s hasn't returned!",
    "%s may have fainted inside...",
    "I'm sick with worry...",
    "We haven't seen each other in a long time.",
    "I have to go!",
    "We have to meet--whatever it takes!",
    "I don't care how--we must meet!",
    "I want to apologize to %s.",
    "I'm close friends with %s!"
};

const char* msgBodyStandard_2Of2_Escort[] = {
    "Please take me to see %s!",
    "Please take me there with you!",
    "Please escort me there!",
    "Someone, please escort me!"
};

const char* msgBodyStandard_1Of2_FindDeliverItem[] = {
    "Having one %s is reassuring.",
    "%s--it's convenient to have.",
    "%s wanted after long search.",
    "%s wanted for exploration.",
    "%s--I'd love to utilize one!",
    "%s--I can't leave without it.",
    "%s wanted as a charm.",
    "%s! Seeking in quantity!",
    "Help this %s collector!",
    "I can't find one more %s.",
    "Hard-to-find %s sought.",
    "%s--I get scared without it!",
    "I can't sleep without it: %s.",
    "%s makes me strong.",
    "%s--it's my mom's favorite.",
    "%s's texture is comforting.",
    "%s wanted to test effects.",
    "%s wanted for nostalgia.",
    "I lost my %s.",
    "Wanted: my own %s.",
    "The item %s is the in thing!",
    "Is it true about the %s?"
};

const char* msgBodyStandard_2Of2_FindDeliverItem[] = {
    "Please! May I have one?",
    "Please trade me one!",
    "Please find one for me!",
    "Please give me one!",
    "Please share one with me!",
    "Please! I must have one delivered!",
    "Please help! Reward offered!",
    "Please! I'm offering a generous reward!",
    "I'm looking forward to your help!",
    "Please let me know if you find one!",
    "Please search for it!",
    "Please help! I'm counting on you!",
    "Please! I need your help!",
    "Please help! You're my only hope!",
    "Please share a little bit!",
    "Please share one with me!",
    "Please! I need some cooperation!",
    "Please help me out!",
    "Please! Please help me!",
    "Please help! I'm offering a reward!",
    "Please help! I'll make it worth your time!",
    "Please contact me if you find it!"
};


/** *** Special flavor texts *** **/

/* Parents */
const int parents[] = {
     15,  13, /* Beedrill   -> Kakuna */
     18,  16, /* Pidgeot    -> Pidgey */
     20,  19, /* Raticate   -> Rattata */
     26, 172, /* Raichu     -> Pichu */
     36, 173, /* Clefable   -> Cleffa */
     40, 174, /* Wigglytuff -> Igglybuff */
    169,  41, /* Crobat     -> Zubat */
     45,  43, /* Vileplume  -> Oddish */
     62,  60, /* Poliwrath  -> Poliwag */
    176, 175, /* Togetic    -> Togepi */
    184, 323, /* Azumarill  -> Azurill */
    242, 241, /* Ursaring   -> Teddiursa */
    257, 256, /* Donphan    -> Phanpy */
    125, 264, /* Electabuzz -> Elekid */
    126, 265, /* Magmar     -> Magby */
    273, 271, /* Tyranitar  -> Larvitar */
    292, 290, /* Beautifly  -> Wurmple */
    331, 329, /* Aggron     -> Aron */
    355, 353, /* Flygon     -> Trapinch */
    393, 391, /* Walrein    -> Spheal */
    302, 301  /* Swellow    -> Taillow */
};

const char* parentsHead = "Save my child!";

const char* parentsBody1Of2[] = {
    "Please rescue Weedle!",
    "Oh, my cute little Pidgey!",
    "Rattata is missing! My precious child!",
    "Please rescue Pichu! He's a little cutie",
    "Cleffa disappeared! Please let me know",
    "Please find Igglybuff! Oh, where did that",
    "Please rescue Zubat! He's so young he",
    "Oddish disappeared from sight! She may be",
    "My baby Poliwag! He wandered off...",
    "Help! Togepi's just a baby!",
    "Please save my adorable Azurill!",
    "Please find Teddiursa! My baby's head",
    "Please look for Phanpy!",
    "My son can be wild with thunderbolts,",
    "My baby Magby is lost. I'm worried sick.",
    "Please search for Larvitar!",
    "My Wurmple went missing! Please look",
    "Please find my Aron!",
    "Please find my little Trapinch!",
    "Save my baby Spheal! My baby is easy to",
    "Please look for Taillow!"
};

const char* parentsBody2Of2[] = {
    "He's my son! Please!",
    "Please, someone help!",
    "Please, won't someone help me?",
    "who can't charge power well yet. Please!",
    "if you find my child!",
    "child roll off to?! Oh!",
    "can't even hang from cavern ceilings well!",
    "buried somewhere! Someone, please help!",
    "He only just learned how to walk! Help!",
    "I'm worried sick! Please help!",
    "Watch for a round and bouncy tail!",
    "has a cute crescent mark! Help!",
    "My son has a distinctive long nose!",
    "but he's kindhearted. Please help!",
    "She's a cheerful child who loves fire.",
    "He loves to eat dirt! I need help!",
    "for the cute spikes on his rear end!",
    "He's my only child! Please help!",
    "My baby is probably lying low!",
    "spot because she likes to roll!",
    "My baby is very timid, so I'm worried!"
};

/* Pairs */
const int pairs[] = {
    103,  85, /* Exeggutor  <-> Dodrio */
     22, 112, /* Fearow     <-> Rhydon */
     90, 394, /* Shellder   <-> Clamperl */
     89, 342, /* Muk        <-> Swalot */
     52, 325, /* Meowth     <-> Skitty */
    129, 374, /* Magikarp   <-> Feebas */
     13, 290, /* Weedle     <-> Wurmple */
    293, 291, /* Cascoon    <-> Silcoon */
    301,  16, /* Taillow    <-> Pidgey */
     37, 347, /* Vulpix     <-> Numel */
    174, 173, /* Igglybuff  <-> Cleffa */
     49, 294, /* Venomoth   <-> Dustox */
    313,  57, /* Vigoroth   <-> Primeape */
    286,  58, /* Poochyena  <-> Growlithe */
     69, 238, /* Bellsprout <-> Shuckle */
     86, 392, /* Seel       <-> Sealeo */
     97, 122, /* Hypno      <-> Mr. Mime */
     98, 366, /* Krabby     <-> Corphish */
    143, 314, /* Snorlax    <-> Slaking */
    127, 239, /* Pinsir     <-> Heracross */
    240, 360, /* Sneasel    <-> Zangoose */
    323, 175, /* Azurill    <-> Togepi */
    132, 185, /* Ditto      <-> Sudowoodo */
    241, 352, /* Teddiursa  <-> Spinda */
     79, 312, /* Slowpoke   <-> Slakoth */
    164, 198, /* Noctowl    <-> Murkrow */
    340, 182, /* Roselia    <-> Bellossom */
    250, 304, /* Delibird   <-> Wingull */
    397,  38, /* Relicanth  <-> Ninetales */
    197, 386, /* Umbreon    <-> Chimecho */
    200, 381, /* Misdreavus <-> Shuppet */
    247, 398, /* Corsola    <-> Luvdisc */
    176, 267, /* Togetic    <-> Blissey */
     32,  29, /* NidoranM   <-> NidoranF */
     33,  30, /* Nidorino   <-> Nidorina */
     34,  31, /* Nidoking   <-> Nidoqueen */
    128, 266, /* Tauros     <-> Miltank */
    338, 339, /* Volbeat    <-> Illumise */
    337, 336, /* Minum      <-> Plusle */
    360, 361, /* Zangoose   <-> Seviper */
    106, 107, /* Hitmonlee  <-> Hitmonchan */
    362, 363, /* Lunatone   <-> Solrock */
    138, 140, /* Omanyte    <-> Kabuto */
    370, 372, /* Lileep     <-> Anorith */
    172, 172  /* Pichu      <-> Pichu */
};

const char* friendsHead  = "Please save my friend!";  /* first 33 */
const char* loversHead   = "Please save my love!";    /* next 7 */
const char* rivalsHead   = "Rescue my rival!";        /* next 4 */
const char* brothersHead = "Please help my brother!"; /* last one */

const char* pairsBody1Of2[] = {
    "This precious friend can chat separately",
    "Please save %s,",
    "Please save my best friend %s!",
    "Please rescue %s.",
    "Please rescue %s!",
    "Help! %s isn't much now, but",
    "Help! I'm friends with %s",
    "We identify with each other because we",
    "%s and I are of the same height.",
    "Please help %s--a good",
    "Please rescue %s!",
    "Without %s, it's no fun playing",
    "%s is really noisy.",
    "I can't play the biting game without my pal",
    "Please help %s! Our cries are",
    "Someone save %s--my friend",
    "We promised each other to perform magic",
    "I want to help %s!",
    "Please help %s! We're both lazy,",
    "I lock horns with %s for fun.",
    "We promised to show each other how",
    "Please help %s!",
    "Without %s around, there's no",
    "Please save %s. We're both alike",
    "...Help... Please...",
    "Without %s, there's no one for",
    "I'm sad without %s's company.",
    "Please save %s. We've been in",
    "Please save %s! We're both",
    "Help %s, please!",
    "I feel lonely without %s to pull",
    "Please rescue %s! The beach",
    "We make each other happy--it's in our",
    "Please! Please rescue %s!",
    "Please rescue my precious %s!",
    "Please rescue %s! We",
    "Please save my %s! Now I",
    "Please save %s!",
    "I can't live without %s!",
    "Please rescue %s! We detest",
    "Please save %s.",
    "%s can't leave without settling",
    "%s has been a rival since my",
    "We've been rivals with %s for",
    "My little brother Pichu disappeared!",
};

const char* pairsBody2Of2[] = {
    "with three heads. Please help!",
    "my drilling buddy!",
    "We're both bivalves!",
    "I can't stand to see a sludge buddy hurt!",
    "We always play together!",
    "my friend is amazing after evolution!",
    "because we both evolve fast! Please help!",
    "both evolved from Wurmple. Please help!",
    "We're lifelong friends! Please help!",
    "friend who shares my love of fire!",
    "We've been friends since we were eggs!",
    "with toxic powders! Someone, please help!",
    "But it's lonely without the racket... Sob...",
    "%s! Please help!",
    "identical! We can tell each other anything!",
    "and rival at ball juggling!",
    "and hypnosis shows together. Please help!",
    "We both have a thing for pincers!",
    "so we're comfortable around each other!",
    "I terribly miss doing that...",
    "sharp our claws could be... Someone, help!",
    "My tiny and round best friend!",
    "one to heckle! Please break my boredom!",
    "in being kind of vacant and unpredictable!",
    "Who was it?",
    "me to play with in the dark! Please help!",
    "We showed flowers to each other...",
    "the delivery business for many years!",
    "old-timers who are longtime friends!",
    "We often took strolls on the wind!",
    "pranks and mess around with. Please help!",
    "feels empty without my usual friend...",
    "nature. Please save %s!",
    "We're madly in love!",
    "We're in love! Please help!",
    "promised our futures together! Please!",
    "know what %s means to me...",
    "We're no good if we're not together!",
    "My heart is breaking! Please! Help!",
    "each other, but we need each other!",
    "We owe each other a game!",
    "which one of us is better. Please help!",
    "ancestors' time. The rivalry can't end!",
    "generations. It can't suddenly end like this!",
    "I'm really worried! Someone, please help!"
};


/* Lovers flavor text - Escort missions */
const int lovers[] = {
     32,  29, /* NidoranM <-> NidoranF */
     33,  30, /* Nidorino <-> Nidorina */
     34,  31, /* Nidoking <-> Nidoqueen */
    128, 266, /* Tauros   <-> Miltank */
    338, 339, /* Volbeat  <-> Illumise */
    337, 336  /* Minum    <-> Plusle */
};

const char* loversEscortHead = "Escort me to my love!";

const char* loversBody1Of2[] = {
    "Please! Take me to meet %s!",
    "Please escort me to my %s!",
    "Help me meet %s!",
    "I really want to meet %s!",
    "I'm so worried about %s...",
    "Without %s, I..."
};

const char* loversBody2Of2[] = {
    "We're in love! Please, take me there!",
    "We belong together! Please escort me!",
    "We've promised our futures together.",
    "This means everything to me!",
    "It's no good if we're not together!",
    "I'm very lonely! Please take me with you!"
};


/* Special missions */
/*
    The following flavors texts are programmed in the game, provided just to complete the database.
    However, only the game can generate the respective Wonder Mail,
    and it also rejects any mail containing the following special missions.
*/
const char* mankeyTitle   = "Punish bad Mankey!";
const char* smeargleTitle = "Smeargle's desperate plea!";
const char* medichamTitle = "Medicham: Help me!";

const char* mankeyBody1Of2   = "Please punish bad Mankey's gang.";
const char* mankeyBody2Of2   = "";
const char* smeargleBody1Of2 = "I didn't want to become a grown-up, so I";
const char* smeargleBody2Of2 = "fled, but now I've lost my way! Help!";
const char* medichamBody1Of2 = "This is Medicham. Rescue me, please!";
const char* medichamBody2Of2 = "The reward is a secret...";

/* Semi-special missions */
const char* evolutionBody1Of2 = "With the item %s, I can";
const char* evolutionBody2Of2 = "evolve! I'm yearning to evolve! Help!";
const char* foodBody1Of2 = "The %s! What I love to eat";
const char* foodBody2Of2 = "and can't live without! Please get one!";


/* Rescue communication (SOS) */
const char* SOS_AskHelp1 = "This is a rescue through communication.";
const char* SOS_AskHelp2 = "Get a friend to help you!";

const char* SOS_GoHelp1  = "This is a rescue through communication.";
const char* SOS_GoHelp2  = "Rescue a friend!";

const char* SOS_Thanks1  = "This is a rescue through communication.";
const char* SOS_Thanks2  = "Send your thanks to your friend!";

/* Pokémon species */
const unsigned int pkmnSpeciesCount = 415; /* The size of the array */
const char* pkmnSpeciesStr[] = {
    "??????????", /* Decamark == Nothing */
    "Bulbasaur",
    "Ivysaur",
    "Venusaur",
    "Charmander",
    "Charmeleon",
    "Charizard",
    "Squirtle",
    "Wartortle",
    "Blastoise",
    "Caterpie", /* 10 */
    "Metapod",
    "Butterfree",
    "Weedle",
    "Kakuna",
    "Beedrill",
    "Pidgey",
    "Pidgeotto",
    "Pidgeot",
    "Rattata",
    "Raticate", /* 20 */
    "Spearow",
    "Fearow",
    "Ekans",
    "Arbok",
    "Pikachu",
    "Raichu",
    "Sandshrew",
    "Sandslash",
    "NidoranF",
    "Nidorina", /* 30 */
    "Nidoqueen",
    "NidoranM",
    "Nidorino",
    "Nidoking",
    "Clefairy",
    "Clefable",
    "Vulpix",
    "Ninetales",
    "Jigglypuff",
    "Wigglytuff", /* 40 */
    "Zubat",
    "Golbat",
    "Oddish",
    "Gloom",
    "Vileplume",
    "Paras",
    "Parasect",
    "Venonat",
    "Venomoth",
    "Diglett", /* 50 */
    "Dugtrio",
    "Meowth",
    "Persian",
    "Psyduck",
    "Golduck",
    "Mankey",
    "Primeape",
    "Growlithe",
    "Arcanine",
    "Poliwag", /* 60 */
    "Poliwhirl",
    "Poliwrath",
    "Abra",
    "Kadabra",
    "Alakazam",
    "Machop",
    "Machoke",
    "Machamp",
    "Bellsprout",
    "Weepinbell", /* 70 */
    "Victreebel",
    "Tentacool",
    "Tentacruel",
    "Geodude",
    "Graveler",
    "Golem",
    "Ponyta",
    "Rapidash",
    "Slowpoke",
    "Slowbro", /* 80 */
    "Magnemite",
    "Magneton",
    "Farfetch'd",
    "Doduo",
    "Dodrio",
    "Seel",
    "Dewgong",
    "Grimer",
    "Muk",
    "Shellder", /* 90 */
    "Cloyster",
    "Gastly",
    "Haunter",
    "Gengar",
    "Onix",
    "Drowzee",
    "Hypno",
    "Krabby",
    "Kingler",
    "Voltorb", /* 100 */
    "Electrode",
    "Exeggcute",
    "Exeggutor",
    "Cubone",
    "Marowak",
    "Hitmonlee",
    "Hitmonchan",
    "Lickitung",
    "Koffing",
    "Weezing", /* 110 */
    "Rhyhorn",
    "Rhydon",
    "Chansey",
    "Tangela",
    "Kangaskhan",
    "Horsea",
    "Seadra",
    "Goldeen",
    "Seaking",
    "Staryu", /* 120 */
    "Starmie",
    "Mr. Mime",
    "Scyther",
    "Jynx",
    "Electabuzz",
    "Magmar",
    "Pinsir",
    "Tauros",
    "Magikarp",
    "Gyarados", /* 130 */
    "Lapras",
    "Ditto",
    "Eevee",
    "Vaporeon",
    "Jolteon",
    "Flareon",
    "Porygon",
    "Omanyte",
    "Omastar",
    "Kabuto", /* 140 */
    "Kabutops",
    "Aerodactyl",
    "Snorlax",
    "Articuno",
    "Zapdos",
    "Moltres",
    "Dratini",
    "Dragonair",
    "Dragonite",
    "Mewtwo", /* 150 */
    "Mew",
    "Chikorita",
    "Bayleef",
    "Meganium",
    "Cyndaquil",
    "Quilava",
    "Typhlosion",
    "Totodile",
    "Croconaw",
    "Feraligatr", /* 160 */
    "Sentret",
    "Furret",
    "Hoothoot",
    "Noctowl",
    "Ledyba",
    "Ledian",
    "Spinarak",
    "Ariados",
    "Crobat",
    "Chinchou", /* 170 */
    "Lanturn",
    "Pichu",
    "Cleffa",
    "Igglybuff",
    "Togepi",
    "Togetic",
    "Natu",
    "Xatu",
    "Mareep",
    "Flaaffy", /* 180 */
    "Ampharos",
    "Bellossom",
    "Marill",
    "Azumarill",
    "Sudowoodo",
    "Politoed",
    "Hoppip",
    "Skiploom",
    "Jumpluff",
    "Aipom", /* 190 */
    "Sunkern",
    "Sunflora",
    "Yanma",
    "Wooper",
    "Quagsire",
    "Espeon",
    "Umbreon",
    "Murkrow",
    "Slowking",
    "Misdreavus", /* 200 */
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown", /* 210 */
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown", /* 220 */
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Unown",
    "Wobbuffet",
    "Girafarig",
    "Pineco",
    "Forretress", /* 230 */
    "Dunsparce",
    "Gligar",
    "Steelix",
    "Snubbull",
    "Granbull",
    "Qwilfish",
    "Scizor",
    "Shuckle",
    "Heracross",
    "Sneasel", /* 240 */
    "Teddiursa",
    "Ursaring",
    "Slugma",
    "Magcargo",
    "Swinub",
    "Piloswine",
    "Corsola",
    "Remoraid",
    "Octillery",
    "Delibird", /* 250 */
    "Mantine",
    "Skarmory",
    "Houndour",
    "Houndoom",
    "Kingdra",
    "Phanpy",
    "Donphan",
    "Porygon2",
    "Stantler",
    "Smeargle", /* 260 */
    "Tyrogue",
    "Hitmontop",
    "Smoochum",
    "Elekid",
    "Magby",
    "Miltank",
    "Blissey",
    "Raikou",
    "Entei",
    "Suicune", /* 270 */
    "Larvitar",
    "Pupitar",
    "Tyranitar",
    "Lugia",
    "Ho-Oh",
    "Celebi",
    "Treecko",
    "Grovyle",
    "Sceptile",
    "Torchic", /* 280 */
    "Combusken",
    "Blaziken",
    "Mudkip",
    "Marshtomp",
    "Swampert",
    "Poochyena",
    "Mightyena",
    "Zigzagoon",
    "Linoone",
    "Wurmple", /* 290 */
    "Silcoon",
    "Beautifly",
    "Cascoon",
    "Dustox",
    "Lotad",
    "Lombre",
    "Ludicolo",
    "Seedot",
    "Nuzleaf",
    "Shiftry", /* 300 */
    "Taillow",
    "Swellow",
    "Wingull",
    "Pelipper",
    "Ralts",
    "Kirlia",
    "Gardevoir",
    "Surskit",
    "Masquerain",
    "Shroomish", /* 310 */
    "Breloom",
    "Slakoth",
    "Vigoroth",
    "Slaking",
    "Nincada",
    "Ninjask",
    "Shedinja",
    "Whismur",
    "Loudred",
    "Exploud", /* 320 */
    "Makuhita",
    "Hariyama",
    "Azurill",
    "Nosepass",
    "Skitty",
    "Delcatty",
    "Sableye",
    "Mawile",
    "Aron",
    "Lairon", /* 330 */
    "Aggron",
    "Meditite",
    "Medicham",
    "Electrike",
    "Manectric",
    "Plusle",
    "Minum",
    "Volbeat",
    "Illumise",
    "Roselia", /* 340 */
    "Gulpin",
    "Swalot",
    "Carvanha",
    "Sharpedo",
    "Wailmer",
    "Wailord",
    "Numel",
    "Camerupt",
    "Torkoal",
    "Spoink", /* 350 */
    "Grumpig",
    "Spinda",
    "Trapinch",
    "Vibrava",
    "Flygon",
    "Cacnea",
    "Cacturne",
    "Swablu",
    "Altaria",
    "Zangoose", /* 360 */
    "Seviper",
    "Lunatone",
    "Solrock",
    "Barboach",
    "Whiscash",
    "Corphish",
    "Crawdaunt",
    "Baltoy",
    "Claydol",
    "Lileep", /* 370 */
    "Cradily",
    "Anorith",
    "Armaldo",
    "Feebas",
    "Milotic",
    "Castform",
    "Castform",
    "Castform",
    "Castform",
    "Kecleon", /* 380 */
    "Shuppet",
    "Banette",
    "Duskull",
    "Dusclops",
    "Tropius",
    "Chimecho",
    "Absol",
    "Wynaut",
    "Snorunt",
    "Glalie", /* 390 */
    "Spheal",
    "Sealeo",
    "Walrein",
    "Clamperl",
    "Huntail",
    "Gorebyss",
    "Relicanth",
    "Luvdisc",
    "Bagon",
    "Shelgon", /* 400 */
    "Salamence",
    "Beldum",
    "Metang",
    "Metagross",
    "Regirock",
    "Regice",
    "Registeel",
    "Latias",
    "Latios",
    "Kyogre", /* 410 */
    "Groudon",
    "Rayquaza",
    "Jirachi",
    "Deoxys",
};


/* Items */
const unsigned int itemsCount = 240; /* The size of the array */
const char* itemsStr[] = {
    "Nothing", /* 0 */
    "Stick",
    "Iron Thorn",
    "Silver Spike",
    "Gold Fang",
    "Cacnea Spike",
    "Corsola Twig",
    "Gravelerock",
    "Geo Pebble",
    "Mobile Scarf",
    "Heal Ribbon", /* 10 */
    "Twist Band",
    "Scope Lens",
    "Patsy Band",
    "No-Stick Cap",
    "Pierce Band",
    "Joy Ribbon",
    "X-Ray Specs",
    "Persim Band",
    "Power Band",
    "Pecha Scarf", /* 20 */
    "Insomniscope",
    "Warp Scarf",
    "Tight Belt",
    "Sneak Scarf",
    "Gold Ribbon",
    "Goggle Specs",
    "Diet Ribbon",
    "Trap Scarf",
    "Racket Band",
    "Def. Scarf", /* 30 */
    "Stamina Band",
    "Plain Ribbon",
    "Special Band",
    "Zinc Band",
    "Detect Band",
    "Alert Specs",
    "Dodge Scarf",
    "Bounce Band",
    "Curve Band",
    "Whiff Specs", /* 40 */
    "No-Aim Scope",
    "Lockon Specs",
    "Munch Belt",
    "Pass Scarf",
    "Weather Band",
    "Friend Bow",
    "Beauty Scarf",
    "Sun Ribbon",
    "Lunar Ribbon",
    "Ring D", /* 50 */
    "Ring E",
    "Ring F",
    "Heal Seed",
    "Wish Stone",
    "Oran Berry",
    "Sitrus Berry",
    "Eyedrop Seed",
    "Reviver Seed",
    "Blinker Seed",
    "Doom Seed", /* 60 */
    "Allure Seed",
    "Life Seed",
    "Rawst Berry",
    "Hunger Seed",
    "Quick Seed",
    "Pecha Berry",
    "Cheri Berry",
    "Totter Seed",
    "Sleep Seed",
    "Plain Seed", /* 70 */
    "Warp Seed",
    "Blast Seed",
    "Ginseng",
    "Joy Seed",
    "Chesto Berry",
    "Stun Seed",
    "Max Elixir",
    "Protein",
    "Calcium",
    "Iron", /* 80 */
    "Zinc",
    "Apple",
    "Big Apple",
    "Grimy Food",
    "Huge Apple",
    "White Gummi",
    "Red Gummi",
    "Blue Gummi",
    "Grass Gummi",
    "Yellow Gummi", /* 90 */
    "Clear Gummi",
    "Orange Gummi",
    "Pink Gummi",
    "Brown Gummi",
    "Sky Gummi",
    "Gold Gummi",
    "Green Gummi",
    "Gray Gummi",
    "Purple Gummi",
    "Royal Gummi", /* 100 */
    "Black Gummi",
    "Silver Gummi",
    "Banana",
    "Chestnut",
    "Poke",
    "Upgrade",
    "King's Rock",
    "Thunderstone",
    "Deepseascale",
    "Deepseatooth", /* 110 */
    "Sun Stone",
    "Moon Stone",
    "Fire Stone",
    "Water Stone",
    "Metal Coat",
    "Leaf Stone",
    "Dragon Scale",
    "Link Cable",
    "Ice Part",
    "Steel Part", /* 120 */
    "Rock Part",
    "Music Box",
    "Key",
    "Used TM",
    "Focus Punch",
    "Dragon Claw",
    "Water Pulse",
    "Calm Mind",
    "Roar",
    "Toxic", /* 130 */
    "Hail Orb",
    "Bulk Up",
    "Bullet Seed",
    "Hidden Power",
    "Sunny Orb",
    "Taunt",
    "Ice Beam",
    "Blizzard",
    "Hyper Beam",
    "Light Screen", /* 140 */
    "Protect",
    "Rainy Orb",
    "Giga Drain",
    "Safeguard",
    "Frustration",
    "Solarbeam",
    "Iron Tail",
    "Thunderbolt",
    "Thunder",
    "Earthquake", /* 150 */
    "Return",
    "Dig",
    "Psychic",
    "Shadow Ball",
    "Brick Break",
    "Evasion Orb",
    "Reflect",
    "Shock Wave",
    "Flamethrower",
    "Sludge Bomb", /* 160 */
    "Sandy Orb",
    "Fire Blast",
    "Rocky Orb",
    "Aerial Ace",
    "Torment",
    "Facade",
    "Secret Power",
    "Rest",
    "Attract",
    "Thief", /* 170 */
    "Steel Wing",
    "Skill Swap",
    "Snatch Orb",
    "Overheat",
    "Wide Slash",
    "Excavate",
    "Spin Slash",
    "See-Trap Orb",
    "Mug Orb",
    "Rebound Orb", /* 180 */
    "Lob Orb",
    "Switcher Orb",
    "Blowback Orb",
    "Warp Orb",
    "Transfer Orb",
    "Slow Orb",
    "Quick Orb",
    "Luminous Orb",
    "Petrify Orb",
    "Stayaway Orb", /* 190 */
    "Pounce Orb",
    "Trawl Orb",
    "Cleanse Orb",
    "Observer Orb",
    "Decoy Orb",
    "Slumber Orb",
    "Totter Orb",
    "Two-Edge Orb",
    "Silence Orb",
    "Escape Orb", /* 200 */
    "Scanner Orb",
    "Radar Orb",
    "Drought Orb",
    "Trapbust Orb",
    "Rollcall Orb",
    "Invisify Orb",
    "One-Shot Orb",
    "Identify Orb",
    "Vacuum-Cut",
    "Reviver Orb", /* 210 */
    "Shocker Orb",
    "Sizebust Orb",
    "One-Room Orb",
    "Fill-In Orb",
    "Trapper Orb",
    "Possess Orb",
    "Itemizer Orb",
    "Hurl Orb",
    "Mobile Orb",
    "Toss Orb", /* 220 */
    "Stairs Orb",
    "Longtoss Orb",
    "Pierce Orb",
    "Cut",
    "Fly",
    "Surf",
    "Strength",
    "Flash",
    "Rock Smash",
    "Waterfall", /* 230 */
    "Dive",
    "Link Box",
    "Switch Box",
    "Weavile Fig",
    "Mime Jr. Fig",
    "Beatup Orb",
    "G Machine 6",
    "G Machine 7",
    "G Machine 8"
};

/* Dungeons */
/* Note: Some of this dungeons are useless in mails because you can't accept such mail, but are still provided as database, there are others unknown dungeons (also invalid values) */
const unsigned int dungeonsCount = 63; /* The size of the array */
const char* dungeonsStr[] = {
    "Tiny Woods", /* 0 */
    "Thunderwave Cave",
    "Mt. Steel",
    "Sinister Woods",
    "Silent Chasm",
    "Mt. Thunder",
    "Mt. Thunder Peak", /* valid, but you can't accept the mail */
    "Great Canyon",
    "Lapis Cave",
    "Mt. Blaze",
    "Mt. Blaze Peak", /* 10, valid, but you can't accept the mail */
    "Frosty Forest",
    "Frosty Grotto", /* valid, but you can't accept the mail */
    "Mt. Freeze",
    "Mt. Freeze Peak", /* valid, but you can't accept the mail */
    "Magma Cavern",
    "Magma Cavern Pit", /* valid, but you can't accept the mail */
    "Sky Tower",
    "Sky Tower Summit", /* valid, but you can't accept the mail */
    "Stormy Sea",
    "Silver Trench", /* 20 */
    "Meteor Cave",
    "Mt. Freeze Peak", /* valid, but you can't accept the mail */
    "Western Cave",
    "[INVALID]", /* invalid */
    "[INVALID]", /* invalid */
    "Wish Cave",
    "Buried Relic",
    "Pitfall Valley",
    "Northern Range",
    "[INVALID]", /* 30, invalid */
    "Desert Region",
    "Southern Cavern",
    "Wyvern Hill",
    "Fiery Field",
    "Northwind Field",
    "Solar Cave",
    "Lightning Field",
    "Darknight Relic",
    "[INVALID]", /* invalid */
    "Murky Cave", /* 40 */
    "Grand Sea",
    "Uproar Forest",
    "Oddity Cave",
    "Remains Island",
    "Marvelous Sea",
    "Fantasy Strait",
    "Rock Path", /* valid, but you can't accept the mail */
    "Snow Path", /* valid, but you can't accept the mail */
    "[INVALID]", /* invalid */
    "[INVALID]", /* 50, invalid */
    "[INVALID]", /* invalid */
    "Dojo Registration", /* valid, but you can't accept the mail */
    "Howling Forest",
    "[INVALID]", /* invalid */
    "Fantasy Strait",
    "Waterfall Pond",
    "Unown Relic",
    "Joyous Tower",
    "Far-off Sea",
    "Mt. Faraway", /* 60 */
    "[INVALID]", /* invalid */
    "Purity Forest",
};


/* Friend areas */
const unsigned int friendAreasCount = 58; /* The size of the array */
const char* friendAreasStr[] = {
    "[Nothing]", /* 0 */
    "Bountiful Sea",
    "Treasure Sea",
    "Serene Sea",
    "Deep-Sea Floor",
    "Deep-Sea Current",
    "Seafloor Cave",
    "Shallow Beach",
    "Mt. Deepgreen",
    "Dragon Cave", /* 9 - Obtainable in missions */
    "Mt. Moonview", /* 10 - Obtainable in missions */
    "Mt. Cleft",
    "Rainbow Peak",
    "Wild Plains",
    "Beau Plains",
    "Sky Blue Plains", /* 15 - Obtainable in missions */
    "Safari",
    "Scorched Plains",
    "Sacred Field",
    "Mist-Rise Forest",
    "Flyaway Forest", /* 20 */
    "Overgrown Forest",
    "Energetic Forest",
    "Mushroom Forest",
    "Healing Forest",
    "Transform Forest",
    "Secretive Forest",
    "Rub-a-Dub River",
    "Tadpole Pond",
    "Turtleshell Pond",
    "Mystic Lake", /* 30 */
    "Waterfall Lake",
    "Peanut Swamp",
    "Poison Swamp",
    "Echo Cave",
    "Cryptic Cave",
    "Jungle",
    "Boulder Cave", /* 37 - Obtainable in missions */
    "Decrepit Lab",
    "Mt. Discipline",
    "Thunder Meadow", /* 40 */
    "Power Plant",
    "Crater",
    "Furnace Desert",
    "Aged Chamber AN",
    "Aged Chamber O?",
    "Ancient Relic",
    "Darkness Ridge",
    "Frigid Cavern",
    "Ice Floe Beach",
    "Volcanic Pit", /* 50 */
    "Stratos Lookout",
    "Ravaged Field",
    "Magnetic Quarry",
    "Legendary Island",
    "Southern Island",
    "Enclosed Island",
    "Final Island"
};

/* Helper texts */
const char* friendZoneText = "Friend Zone";
const char* nearPlaceText  = "Near";
