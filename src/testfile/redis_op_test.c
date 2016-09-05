#include "redis_op.h"
#include "make_log.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MODULE_NAME "fdfs_client_test"
#define PROC_NAME   "fdfs_client_test_main"

#define SERVER_IP	"127.0.0.1"
#define SERVER_PORT	"6379"

int main(int argc, char *argv[])
{
	int ret = 0;
	char *key = "age";
	char *str = "128";
	char return_value[256] = { 0 };
	redisContext* conn = NULL;
	
	conn = rop_connectdb_nopwd(SERVER_IP, SERVER_PORT);
	if(conn == NULL)
	{
		printf("Func rop_connectdb_nopwd error\n");
		LOG(MODULE_NAME, PROC_NAME, "Func rop_connectdb_nopwd error");
		return;
	}
	printf("rop_connectdb_nopwd succ\n");
	
	ret = rop_set_key(conn, key, str);
	if(ret != 0)
	{
		printf("rop_set_key set %s %s error\n", key, str);
	}
	else
	{
		printf("rop_set_key set %s %s OK\n", key, str);
	}
	
	ret = rop_get_key(conn, key, return_value);
	if(ret != 0)
	{
		printf("rop_get_key get %s error\n", key);
	}
	else
	{
		printf("rop_get_key get %s %s OK\n", key, return_value);
	}
	
	rop_disconnect(conn);
	
	return 0;
}