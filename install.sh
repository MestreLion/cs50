#!/bin/bash

# Install Harvard's CS50 repos, C and Python libraries and CLI tools

# https://github.com/cs50/libcs50
# https://packagecloud.io/install/repositories/cs50/repo/script.deb.sh

#------------------------------------------------------------------------------

set -Eeuo pipefail
trap 'error "line $LINENO, status $?: $BASH_COMMAND"' ERR

#------------------------------------------------------------------------------

gpg_key_url="https://packagecloud.io/cs50/repo/gpgkey"
apt_config_url="https://packagecloud.io/install/repositories/cs50/repo/config_file.list?source=script"
apt_source_path="/etc/apt/sources.list.d/cs50.list"

#------------------------------------------------------------------------------

os=
dist=
update=0

#------------------------------------------------------------------------------

try()     { "$@" 2>/dev/null || :; }
bold()    { try tput bold; printf '%s' "$@"; try tput sgr0; echo; }
color()   { if (($# > 1)); then try tput setaf "$1"; shift; bold "$@"; fi; }
red()     { color 1 "$@"; }
green()   { color 2 "$@"; }
yellow()  { color 3 "$@"; }
blue()    { color 4 "$@"; }
fatal()   { red "${0##*/}: fatal${1:+: $@}" >&2; exit 1; }
message() { green "* $@"; }

#------------------------------------------------------------------------------

package_installed() {
	dpkg-query --showformat='${Version}' --show "$1" &>/dev/null
}

apt_install() {
	# Install all non-existing packages in a single command
	# Usage: package_install [PACKAGE...]
	local pkg=
	local pkgs=()
	for pkg in "$@"; do
		if ! package_installed "$pkg"; then pkgs+=( "$pkg" ); fi
	done
	if (("${#pkgs[@]}")); then
		sudo apt install -y "${pkgs[@]}"
	fi
}

pip_install() {
	local pak=
	for pak in "$@"; do
		if pip3 show "$pak" &>/dev/null; then continue; fi
		pip3 install --user "$pak"
	done
}


detect_os () {
	# some systems dont have lsb-release yet have the lsb_release binary and
	# vice-versa
	if [ -e /etc/lsb-release ]; then
		. /etc/lsb-release

		if [ "${ID:-}" = "raspbian" ]; then
			os=${ID}
			dist=`cut --delimiter='.' -f1 /etc/debian_version`
		else
			os=${DISTRIB_ID}
			dist=${DISTRIB_CODENAME}
			if [ -z "$dist" ]; then
				dist=${DISTRIB_RELEASE}
			fi
		fi

	elif [ `which lsb_release 2>/dev/null` ]; then
		dist=`lsb_release -c | cut -f2`
		os=`lsb_release -i | cut -f2 | awk '{ print tolower($1) }'`

	elif [ -e /etc/debian_version ]; then
		# some Debians have jessie/sid in their /etc/debian_version
		# while others have '6.0.7'
		os=`cat /etc/issue | head -1 | awk '{ print tolower($1) }'`
		if grep -q '/' /etc/debian_version; then
			dist=`cut --delimiter='/' -f1 /etc/debian_version`
		else
			dist=`cut --delimiter='.' -f1 /etc/debian_version`
		fi
	fi

	# remove whitespace from OS and dist name
	os="${os// /}"
	dist="${dist// /}"

	echo "Detected operating system as $os/$dist."
	if [ -z "$dist" ]; then
		echo "Your OS distro or version are not supported."
		exit 1
	fi
}

message "Install Harvard's CS50 repositories, C and Python libraries and CLI tools"

if ! package_installed libcs50; then
	detect_os

	apt_config_url+="&os=${os}&dist=${dist}"
	message "Repository URL: $apt_config_url"

	# create an apt config file for this repository
	message "Installing $apt_source_path"
	curl -sSf "${apt_config_url}" | sudo tee "$apt_source_path" > /dev/null

	# import the gpg key
	message "Importing packagecloud gpg key"
	curl -L "${gpg_key_url}" | sudo apt-key add -

	update=1
fi

if ! package_installed astyle; then
	message "Adding CS50 PPA Repository"
	sudo add-apt-repository ppa:cs50/ppa
	update=0  # add-apt-repository does apt update
fi

if ((update)); then
	message "Updating apt package list"
	sudo apt update
fi

message "Installing CS50 C library, CLI dependencies and tools"
apt_install libcs50 astyle valgrind

message "Installing CS50 Python library and main CLI tools"
pip_install {cs,check,style,submit}50

message "Configuring SSH so check50 and submit50 do not ask for Github password"
ssh -T -p443 git@ssh.github.com || :

message "Done!"
