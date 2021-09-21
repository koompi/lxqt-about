pkgname=koompi-lxqt-about
pkgver=0.17.0
pkgrel=3
pkgdesc="LXQT about dialog."
arch=("x86_64" "aarch64" "armv7h")
groups=("lxqt")
provides=("lxqt-about")
conflicts=("lxqt-about")
license=("LGPL2.1")
depends=("liblxqt" "libQt5Xdg.so")
makedepends=("lxqt-build-tools" "tar" "gzip")
source=(
	"https://github.com/koompi/lxqt-about/archive/refs/tags/0.17.0-3.tar.gz"
	"koompi.svg"
)
sha256sums=(
	'a23e996f1c06c97262615ada3ce682919f2fcfea112fb999a18c424e501cb154'
	'50e4b89a439466067bb2a5eb3ba010c9cda8c10a64bdd57614556752c946aef8'
)

prepare(){
	cd "${srdir}"
	tar -xzvpf "${pkgver}-${pkgrel}".tar.gz -C .
}


build() {
	mkdir -p build
	cd build
	cmake "$srcdir/lxqt-about-${pkgver}-${pkgrel}" \
		-DCMAKE_INSTALL_PREFIX=/usr
	make
}

package() {
	cd build
	make DESTDIR="$pkgdir" install

	install -D "${srcdir}/koompi.svg" "${pkgdir}/usr/share/icons/koompi.svg"
}
