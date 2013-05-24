Pandemoonium
============

Pandemoonium! USACO 2013

## Have questions?

~~Try the [FAQ/Wiki](http://github.com/usaco/Pandemoonium/wiki).~~

## Need updates?

If you need to update your local copy, navigate to `Pandemoonium/` and try:

```bash
git pull origin master
```

## What is Pandemoonium?

You take the role of a farmer, competing against other farmers, trying to get as much milk as possible in one day. A day is subdivided into rounds. Each cow can produce a fixed amount of milk per round. In each round, each farmer simultanously chooses a cow to milk. If more than one farmer selects the same cow, they subdivide the milk evenly (rounded down to the next largest integer -- fighting causes spillage!). At the end of the day, the farmer with the most milk is the winner.

## How do I get started?

Begin by cloning a copy of the Git repo:

```bash
git clone git://github.com/usaco/Pandemoonium.git
```

Go to the `base/` directory and compile the driver:

```bash
cd Pandemoonium/base
make
```

This will create the Pandemoonium driver.

Next, build the example bots to help with testing:

```bash
cd ../bots
bash build-all.sh
```

Make a new bot to begin working. A helper script has been provided for this purpose.

```bash
cd ..
bash setup-bot.sh "My Awesome Bot"
```

This will create a new directory `MyAwesomeBot/` in the directory `bots/`.
