# Copyright 1999-2009 Gentoo Foundation
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

DEPEND="dev-util/pkgconfig"
RDEPEND=""

src_configure() {
	cmake-utils_src_configure
}
