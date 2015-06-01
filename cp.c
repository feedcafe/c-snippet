#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define HCI_LOGGING_FILENAME	"/data/misc/bluedroid/btsnoop_hci.log"
#define HCI_LOGGING_BACKUP	"/data/misc/bluedroid/btsnoop_hci.old"

#define BUF_SIZE		1024

int btsnoop_log_backup(char *logfile)
{
	char btsnoop_backup[256] = HCI_LOGGING_BACKUP;
	char buf[BUF_SIZE];
	char *ptr;

	int hci_backup_fd = -1;
	int hci_btsnoop_fd = -1;

	int bytes_read, bytes_wrote;

        hci_btsnoop_fd = open(logfile, O_RDONLY);
        if (hci_btsnoop_fd == -1) {
            fprintf(stderr, "btsnoop_log_open: Unable to open snoop log file\n");
            hci_btsnoop_fd = -1;
            return 0;
        }

        hci_backup_fd = open(btsnoop_backup, O_WRONLY|O_CREAT|O_TRUNC,
                              S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH);
        if (hci_backup_fd == -1) {
            fprintf(stderr, "btsnoop_log_open: Unable to open backup log file\n");
            hci_backup_fd = -1;
            return 0;
        }

	while ((bytes_read = read(hci_btsnoop_fd, buf, BUF_SIZE))) {
		if (bytes_read < 0)
			break;
		ptr = buf;
		while ((bytes_wrote = write(hci_backup_fd, ptr, bytes_read))) {
			if (bytes_wrote < 0) {
				fprintf(stderr, "write to backup file failed\n");
				break;
			} else if (bytes_wrote == bytes_read)
				break;

			ptr += bytes_wrote;
			bytes_read -= bytes_wrote;
		}

		if (bytes_wrote < 0) {
			fprintf(stderr, "write to backup file failed\n");
			break;
		}

	}
	close(hci_btsnoop_fd);
	close(hci_backup_fd);

	return 0;
}

int main()
{
	char btsnoop_logfile[256] = HCI_LOGGING_FILENAME;

	btsnoop_log_backup(btsnoop_logfile);

	return 0;
}
