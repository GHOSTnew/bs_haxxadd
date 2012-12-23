#include "module.h"

#define AUTHOR "GHOSTnew"
#define VERSION "1.0.0"

    /* -----------------------------------------------------------*
     * Name  : bs_haxxadd                                         *
     * Author: GHOSTnew <GHOSTnew.geek@gmail.com>                 *
     * Date: 03/12/2012                                           *
     * -----------------------------------------------------------*
     * Tested: Unreal32                                           *
	 * -----------------------------------------------------------*
	 * Code pour simplifier la vie plutot que de taper la commande*
	 * suivante: "/msg chanserv vop add username" on poura tous   *
	 * simplement taper "!vop add username"                       *
     * -----------------------------------------------------------*
     *                                                            *
     * ------------------------Commands---------------------------*
     * !sop {add | del | clear} <nick>                            *
     * Modifie la liste des utilisateurs SOPs                     *
     * -----------------------------------------------------------*
     * !aop {add | del | clear} <nick>                            *
     * Modifie la liste des utilisateurs AOPs                     *
     * -----------------------------------------------------------*
     * !hop {add | del | clear} <nick>                            *
     * Configure la liste des HOPs d'un canal (HalfOP)            *
     * -----------------------------------------------------------*
     * !vop {add | del | clear} <nick>                            *
     *  Configure la liste des VOPs pour un canal (VoicePeople)   *
     * -----------------------------------------------------------*
     */

int my_privmsg(char *source, int ac, char **av);

int mynewmsg(User * u, ChannelInfo * ci, char *my_buffer);


int AnopeInit(int argc, char **argv)
{

    if ((strcmp(version_protocol, "UnrealIRCd 3.2+")) && (strcmp(version_protocol, "UnrealIRCd 3.1.1+"))) {
        alog("[bs_haxxadd] ERROR: IRCd non supporte.");
        alog("[bs_haxxadd] Initiating auto-shutdown.");

        return MOD_STOP;
    }

    Message *msg = NULL;

    int status;

    msg = createMessage("PRIVMSG", my_privmsg);

    status = moduleAddMessage(msg, MOD_HEAD);

    alog("Loading module bs_haxxadd [Status: %d]", status);

    moduleAddAuthor(AUTHOR);

    moduleAddVersion(VERSION);

    return MOD_CONT;

}

void AnopeFini(void)
{

    alog("Unloading bs_haxxadd");

}


int my_privmsg(char *source, int ac, char **av)
{
    User *u;
    ChannelInfo *ci;
    char *my_buffer = NULL;


    if (ac != 2)
        return MOD_CONT;
    if (!(u = finduser(source))) {
        return MOD_CONT;
    }
    if (*av[0] == '#') {
        if (s_BotServ && (ci = cs_findchan(av[0])))
            if (!(ci->flags & CI_VERBOTEN) && ci->c && ci->bi) {
                my_buffer = sstrdup(av[1]);
                if (my_buffer) {
                    if (my_buffer[0] == '!')
                        mynewmsg(u, ci, my_buffer);
                    free(my_buffer);
                }
            }
    }
    return MOD_CONT;
}

int mynewmsg(User * u, ChannelInfo * ci, char *my_buffer)
{

    char *cmd = NULL;

    char *param1 = NULL;

    char *param2 = NULL;

    char *param3 = NULL;

    char *param4 = NULL;

    char *param5 = NULL;

    char *params = NULL;

    char dilim = ' ';


    cmd = myStrGetToken(my_buffer, dilim, 0);


    param1 = myStrGetToken(my_buffer, dilim, 1);

    param2 = myStrGetToken(my_buffer, dilim, 2);

    param3 = myStrGetToken(my_buffer, dilim, 3);

    param4 = myStrGetToken(my_buffer, dilim, 4);

    param5 = myStrGetToken(my_buffer, dilim, 5);

    params = moduleGetLastBuffer();

    if (!cmd)
        return MOD_CONT;


/*
 *les commandes
 */

    if (ci->botflags & BS_FANTASY) {

        if (!stricmp(cmd, "!sop")) {

            if (!param1) {
			
                notice(whosends(ci), u->nick,
                       "SYNTAX: !sop {add | del | clear} <nick> ");
					   
            }else if (!stricmp(param1, "add")
                    || (!stricmp(param1, "del"))) {
			
			    if(!param2) {
				
			        notice(whosends(ci), u->nick,
                           "SYNTAX: !sop {add | del | clear} <nick> ");
						   
			    }else if(param2) {
				
				    User *u2;

                    Channel *c2;
					
					c2 = findchan(ci->name);
					
					if ((u2 = finduser(param2))) {

					send_cmd(ci->bi->nick, "MSG CHANSERV SOP %s %s %s", ci->name, param1,
                                 param2);
								 
                        notice(whosends(ci), u->nick,
                               "%s a été ajouté a la liste des SOP ", param2);
                    }

                    else {

                        notice(whosends(ci), u->nick,
                               "%s ne peut etre ajouté a la liste des SOP, %s n'est pas conecté !",
                               param2, param2);
                    }
				}
			}else if (!stricmp(param1, "clear")){
			
			    send_cmd(ci->bi->nick, "MSG CHANSERV SOP %s %s", ci->name, param1);
				
				notice(whosends(ci), u->nick,
                               "la liste des SOP à été vidé");
			}

        }
		else if(!stricmp(cmd, "!aop")) {

            if (!param1) {
                notice(whosends(ci), u->nick,
                       "SYNTAX: !aop {add | del | clear} <nick> ");
					   
            }else if(!stricmp(param1, "add")
                    || (!stricmp(param1, "del"))) {
			
			    if(!param2) {
				
			        notice(whosends(ci), u->nick,
                           "SYNTAX: !sop {add | del | clear} <nick> ");
						   
			    }
				else if(param2) {
				
				    User *u2;

                    Channel *c2;
					
					c2 = findchan(ci->name);
					
					if((u2 = finduser(param2))) {

					send_cmd(ci->bi->nick, "MSG CHANSERV AOP %s %s %s", ci->name, param1,
                                 param2);
								 
                        notice(whosends(ci), u->nick,
                               "%s a été ajouté a la liste des AOP ", param2);
                    }

                    else {

                        notice(whosends(ci), u->nick,
                               "%s ne peut etre ajouté a la liste des AOP, %s n'est pas conecté !",
                               param2, param2);
                    }
				}
			}else if(!stricmp(param1, "clear")){
			
			    send_cmd(ci->bi->nick, "MSG CHANSERV AOP %s %s", ci->name, param1);
				
				notice(whosends(ci), u->nick,
                               "la liste des AOP à été vidé");
			}

        }else if(!stricmp(cmd, "!hop")) {

            if (!param1) {
			
                notice(whosends(ci), u->nick,
                       "SYNTAX: !hop {add | del | clear} <nick> ");
					   
            }else if(!stricmp(param1, "add")
                    || (!stricmp(param1, "del"))) {
			
			    if(!param2) {
				
			        notice(whosends(ci), u->nick,
                           "SYNTAX: !hop {add | del | clear} <nick> ");
						   
			    }else if(param2) {
				
				    User *u2;

                    Channel *c2;
					
					c2 = findchan(ci->name);
					
					if ((u2 = finduser(param2))) {

					send_cmd(ci->bi->nick, "MSG CHANSERV HOP %s %s %s", ci->name, param1,
                                 param2);
								 
                        notice(whosends(ci), u->nick,
                               "%s a été ajouté a la liste des HOP ", param2);
                    }

                    else {

                        notice(whosends(ci), u->nick,
                               "%s ne peut etre ajouté a la liste des HOP, %s n'est pas conecté !",
                               param2, param2);
                    }
				}
			}else if(!stricmp(param1, "clear")){
			
			    send_cmd(ci->bi->nick, "MSG CHANSERV HOP %s %s", ci->name, param1);
				
				notice(whosends(ci), u->nick,
                               "la liste des HOP à été vidé");
			}

        }else if(!stricmp(cmd, "!vop")) {

            if(!param1) {
                notice(whosends(ci), u->nick,
                       "SYNTAX: !vop {add | del | clear} <nick> ");	   
            }
			else if(!stricmp(param1, "add")
                    || (!stricmp(param1, "del"))) {
			
			    if(!param2) {
				
			        notice(whosends(ci), u->nick,
                           "SYNTAX: !vop {add | del | clear} <nick> ");
						   
			    }else if(param2) {
				
				    User *u2;

                    Channel *c2;
					
					c2 = findchan(ci->name);
					
					if ((u2 = finduser(param2))) {

					send_cmd(ci->bi->nick, "MSG CHANSERV VOP %s %s %s", ci->name, param1,
                                 param2);
								 
                        notice(whosends(ci), u->nick,
                               "%s a été ajouté a la liste des vOP ", param2);
                    }

                    else {

                        notice(whosends(ci), u->nick,
                               "%s ne peut etre ajouté a la liste des VOP, %s n'est pas conecté !",
                               param2, param2);
                    }
				}
			}else if(!stricmp(param1, "clear")){
			
			    send_cmd(ci->bi->nick, "MSG CHANSERV VOP %s %s", ci->name, param1);
				
				notice(whosends(ci), u->nick,
                               "la liste des vOP à été vidé");
			}

        }

    }
}