package com.item;

public class ItemDirector {

    // Director pentru builder, construieste diferite iteme predefinite

    // Metoda construct apeleaza on alta metoda din aceasta clasa, in functie de un
    // string primit ca parametru
    public void construct(String item, ItemBuilder builder){
        switch (item) {
            case ("scut") -> constructScut(builder);
            case ("vesta") -> constructVesta(builder);
            case ("sabiuta") -> constructSabiuta(builder);
            case ("bagheta") -> constructBagheta(builder);
            case ("vitamine") -> constructVitamine(builder);
            case ("brad") -> constructBrad(builder);
            case ("pelerina") -> constructPelerina(builder);
        }
    }

    public void constructScut(ItemBuilder builder){
        builder.setItemType(ItemType.scut);
        builder.setDefense(2);
        builder.setSpecialDefense(2);
    }

    public void constructVesta(ItemBuilder builder){
        builder.setItemType(ItemType.vesta);
        builder.setHp(10);
    }

    public void constructSabiuta(ItemBuilder builder){
        builder.setItemType(ItemType.sabiuta);
        builder.setAttack(3);
    }

    public void constructBagheta(ItemBuilder builder){
        builder.setItemType(ItemType.bagheta);
        builder.setSpecialAttack(3);
    }

    public void constructVitamine(ItemBuilder builder){
        builder.setItemType(ItemType.vitamine);
        builder.setHp(2);
        builder.setAttack(2);
        builder.setSpecialAttack(2);
    }

    public void constructBrad(ItemBuilder builder){
        builder.setItemType(ItemType.brad);
        builder.setAttack(3);
        builder.setDefense(1);
    }

    public void constructPelerina(ItemBuilder builder){
        builder.setItemType(ItemType.pelerina);
        builder.setSpecialDefense(3);
    }
}
