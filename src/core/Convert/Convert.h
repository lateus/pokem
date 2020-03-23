#ifndef CONVERT_H
#define CONVERT_H

/* CONVERTING SOS MAIL FUNCTIONS */
int convertSosMail(const char *SOSPassword, int idTeamGivingHelp, int item, char *resultAOKMail, char *resultThankYouMail);
void convertSosToAOkMail(char *password54Integers, int idTeamGivingHelp);
void convertAOkToThankYouMail(char *password54Integers, int item);

#endif /* CONVERT_H */
