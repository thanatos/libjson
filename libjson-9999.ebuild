# Copyright (C) 2009 Roy Wellington IV
# Distributed under the terms of the GNU General Public License v2
# $Header: $

EAPI=2

inherit cmake-utils git

DESCRIPTION="@PACKAGE_DESCRIPTION@"
HOMEPAGE=""

EGIT_REPO_URI="git://github.com/thanatos/libjson.git"
EGIT_BRANCH="master"

LICENSE="MIT"
SLOT="0"
KEYWORDS="~amd64 ~x86"
IUSE=""

DEPEND=""
RDEPEND=""

src_configure() {
	cmake-utils_src_configure
}
