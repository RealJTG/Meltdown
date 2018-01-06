/* ---------------------------------------------------------------------
 * 
 * DISCLAIMER
 * 
 * ---------------------------------------------------------------------
 * 
 * Author takes no responsibility for any actions with provided 
 * informations or codes. The copyright for any material created by the 
 * author is reserved. Any duplication of codes or texts provided here in 
 * electronic or printed publications is not permitted without the 
 * author's agreement. For personal and non-commercial use only.
 * 
 * ---------------------------------------------------------------------
 * 
 * Speculative optimizations execute code in a non-secure manner leaving 
 * data traces in microarchitecture such as cache.
 *
 * Refer to the paper by Lipp et. al 2017 for details: 
 * https://meltdownattack.com/meltdown.pdf.
 * 
 * ---------------------------------------------------------------------
 * 
 * Exploited by BuddasLittleFinger
 * 
 * Tested on:
 * 
 * Ubuntu 16.04
 * CentOS 7.2
 * 
 * Kudos for:
 * Vasyan, Mews, Laurent Pootie(cat) and all the mates i know, peace.
 * Special kudos for Zhabka for testing this shit. 
 *
 */


#define _GNU_SOURCE
#define _XOPEN_SOURCE

#include <stdio.h>
#include <string.h>
#include <setjmp.h>
#include <signal.h>
#include <ucontext.h>
#include <unistd.h>
#include <fcntl.h>

#include <x86intrin.h>

// #define DEBUG 1

/* comment out if getting illegal insctructions error */

#ifndef HAVE_RDTSCP
#define HAVE_RDTSCP 1
#endif


#define TARGET_OFFSET 9
#define TARGET_SIZE (1 << TARGET_OFFSET)
#define BITS_BY_READ    2


static char target_array[BITS_BY_READ * TARGET_SIZE];


void clflush_target(void)
{
    int i;

    for (i = 0; i < BITS_BY_READ; i++)
        _mm_clflush(&target_array[i * TARGET_SIZE]);
}


const char * array[] = {
    "We're no strangers to love",
    "You know the rules and so do I",
    "A full commitment's what I'm thinking of",
    "You wouldn't get this from any other guy",
    "",
    "I just wanna tell you how I'm feeling",
    "Gotta make you understand",
    "",
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",
    "Never gonna say goodbye",
    "Never gonna tell a lie and hurt you",
    "",
    "We've known each other for so long",
    "Your heart's been aching but you're too shy to say it",
    "Inside we both know what's been going on",
    "We know the game and we're gonna play it",
    "",
    "And if you ask me how I'm feeling",
    "Don't tell me you're too blind to see",
    "",
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",
    "Never gonna say goodbye",
    "Never gonna tell a lie and hurt you",
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",
    "Never gonna say goodbye",
    "Never gonna tell a lie and hurt you",
    "",
    "Never gonna give, never gonna give",
    "(Give you up)",
    "(Ooh) Never gonna give, never gonna give",
    "(Give you up)",
    "",
    "We've known each other for so long",
    "Your heart's been aching but you're too shy to say it",
    "Inside we both know what's been going on",
    "We know the game and we're gonna play it",
    "",
    "I just wanna tell you how I'm feeling",
    "Gotta make you understand",
    "",
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",
    "Never gonna say goodbye",
    "Never gonna tell a lie and hurt you",
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",
    "Never gonna say goodbye",
    "Never gonna tell a lie and hurt you",
    "Never gonna give you up",
    "Never gonna let you down",
    "Never gonna run around and desert you",
    "Never gonna make you cry",  
};

#define n_array (sizeof (array) / sizeof (const char *))

int main(int argc, char *argv[])
{   
    size_t i;

    for (i = 0; i < n_array; i++) {
        printf ("%s\n", array[i]);
    }
    return 0;
}
